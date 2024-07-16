/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:56:31 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 13:56:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/* MAP ERRORS
	1. Read map => In order to get the size (width / height) => DONE
		a. Check if empty map.
		b. Open file
		c. Loop to get the size of the map.
	2. Malloc the map => DONE
	3. Fill the map =>Same as the first step. => DONE
		a. Open the file
		b. Loop to fill our map. 
		On malloc que le contenu et plus la map dans son ensemble !
	4. Wall map errors
		a. Check des caractères sur les murs (non autorisés)
		b. x 4 pour réaliser tous les murs !
	5. Map shape errors
		a. Check si la map est carrée (par contre check JB's tickets car
		la map n'est pas toujours carrée mais il faut qd même le check).
	6. Check la sortie de la map (relevant ?)
	7. Check collectibles (relevant ?)
	8. Check player
	9. Char errors on map
	10. Check Floofill errors
		a. Fill the temp map for floodfill
		b. Checking issues on map ways
*/

// line_length = 0; Autre on passe les elements + le vide et on arrive a la map.
void	read_map(t_game *game, const char *file)
{
	int		fd;
	char	*line;
	int		line_length;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	line_length = 0;
	while (1)
	{
		// Si ligne vide => je break la boucle
		// printf("Height: %d\n", game->map.height);
		// Check par ordre des lignes donc ligne X est ca.
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (check_char(line, '1') == 1 && check_char(line, 'F') == 0
			&& check_char(line, 'C') == 0)
		{
			line_length = ft_strlen(line);
			if (line[line_length - 1] == '\n')
				line_length--;
			if (line_length > game->map.width)
				game->map.width = line_length;
			game->map.height++;
		}
		free(line);
	}
	close(fd);
}

void	malloc_map(t_game *game)
{
	// printf("Height : %d\n", game->map.height);
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (game->map.map == NULL)
	{
		printf("Could not allocate memory\n");
		return ;
	}
	game->map.map[game->map.height] = NULL;
}

void	fill_map(t_game *game, const char *file)
{
	int		i;
	int		fd;
	int		textures;
	int		rgb;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	textures = 0;
	rgb = 0;
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	while (1) // CHECK IF AU MOINS LIGNE DE VIDE AVEC UN FLAG!!!
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		// printf("map : %s\n", line);
		if (textures != 4 && is_path_textures(game, line, textures) == 0)
			textures += 1;
		else if (rgb != 2 && is_rgb_code(game, line) == 0)
			rgb += 1;
		else if ((check_char(line, '1') == 1 || check_char(line, '0') == 1)
			&& (check_char(line, 'F') == 0 && check_char(line, 'C') == 0)) // Pas bon car va me mettre les lignes avec espaces et tout !
		{
			if (i >= game->map.height)
			{
				printf("Error: map height exceeded allocated space\n");
				free(line);
				break ;
			}
			// printf("map : %s\n", line);
			game->map.map[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	printf("RGB : %d\n", rgb);
	printf("Textures : %d\n", textures);
	if (rgb != 2 || textures != 4)
	{
		printf("Map description is either wrong or incomplete\n");
		free_all2(game);
	}
	close(fd);
}
/*
	While (gnl)
	{
		soit compteur pour savoir le nb de ligne
		OU
		parse ligne 1 > gnl > parse ligne 2 > gnl > etc.
	}
	*/
	// i = 0;
	// while (game->map.map[i])
	// {
	// 	printf("map : %s\n", game->map.map[i]);
	// 	i++;
	// }

/*
if (*line == ',')
=> Should we manage the error ? Yes !
*/
int	parse_rgb(char *line, int *r, int *g, int *b)
{
	*r = ft_atoi2(line);
	if (*r == -1)
		return (printf("Red color code is missing\n"), 1);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	else
		return (1);
	*g = ft_atoi2(line);
	if (*g == -1)
		return (printf("Green color code is missing\n"), 1);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	else
		return (1);
	*b = ft_atoi2(line);
	if (*b == -1)
		return (printf("Blue color code is missing\n"), 1);
	while (ft_isdigit(*line))
		line++;
	if (*line != '\0' && *line != '\n')
		return (1);
	if ((*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		&& ft_isspace(line) != 1)
		return (1);
	return (0);
}
//  && !isspace(*line) - Should we check the end of the line ?

// Check si 2 fois same rgb !
int	is_rgb_code(t_game *game, char *line)
{
	int		r;
	int		g;
	int		b;
	char	*rgb_line;

	if ((line[0] == 'C' || line[0] == 'F') && line[1] == ' ')
	{
		rgb_line = line + 2;
		if (parse_rgb(rgb_line, &r, &g, &b) == 1)
		{
			if (line[0] == 'C')
				printf("Invalid ceiling RGB color\n");
			else
				printf("Invalid floor RGB color\n");
			free_all2(game);
		}
		if (line[0] == 'F')
		{
			game->floor.r = r;
			game->floor.g = g;
			game->floor.b = b;
		}
		else if (line[0] == 'C')
		{
			game->ceiling.r = r;
			game->ceiling.g = g;
			game->ceiling.b = b;
		}
		return (0);
	}
	else if (check_char(line, 32) != 1 && check_char(line, '\n') != 1)
	{
		printf("Invalid id for RGB color\n");
		free(line);
		free_all2(game);
	}
	return (1);
}

int	is_path_textures(t_game *game, char *line, int textures)
{
	(void)textures;
	if (ft_strncmp(line, "NO", 2) == 0 && line[2] == ' ')
		game->texture_paths[0] = ft_strdup(line);
	else if (ft_strncmp(line, "SO", 2) == 0 && line[2] == ' ')
		game->texture_paths[1] = ft_strdup(line);
	else if (ft_strncmp(line, "WE", 2) == 0 && line[2] == ' ')
		game->texture_paths[2] = ft_strdup(line);
	else if (ft_strncmp(line, "EA", 2) == 0 && line[2] == ' ')
	{
		game->texture_paths[3] = ft_strdup(line);
		game->texture_paths[4] = NULL;
	}
	// else
	// {
	// 	printf("Invalid/Missing texture(s)\n");
	// 	free(line);
	// 	free_all2(game);
	// }
	else
		return (1);
	return (0);
}

void	manage_errors(t_game *game, const char *file)
{
	if (is_file_valid(file, game) == 1)
		free_all2(game);
	if (is_map_valid(game) == 1)
		free_all2(game);
}

/* ERRORS TO HANDLE
Errors map : 
Validiter du fichier .cub => DONE
1er ligne start avec NO puis un ' ' puis save toute la ligne jusquau '\n' => DONE
SO pareil => DONE
WE pareil => DONE
EA pareil => DONE
ligne 5 only authorize (\t \n ' ' etc, ...)
F int,int,int (compris entre 0 et 255) => DONE
C ligne 8 only authorize (\t \n ' ' ect...) => DONE
AP (a partir de la rien dautoriser hors ' ' 1 0) fin de la map quand une ligne 
commence par \n,
apres cela aucun char autoriser hors \n


Message a afficher en cas de probleme d'input :

Manque un espace entre North/South/East/West/Floor/Ceiling et leur valeur

Path invalide pour North/South/East/West => Floodfill (aucun 0 qui touche un 
espace) !

Manque une ligne vide entre les textures et les couleurs (ligne 5)

Manque une ligne vide entre les couleurs et la map (ligne 8)

Map invalide, Char interdit dans la map ( /1/0)

Map invalide, la map doit etre entourer de mur (tips sur lalgo de graph)

Aucun char autoriser apres la fin de la map (apres une premiere ligne vide 
post map)

*/

/* ERRORS TO HANDLE
Voici un exemple de toutes les erreurs qui doivent être traitées dans le ticket 
parsing ou init :

"Not a .cub file" => OK
"Not an .xpm file"
"Invalid floor/ceiling RGB color(s)" => DONE
"One color code is missing" => DONE
"Invalid floor RGB color" => DONE
"Invalid ceiling RGB color" => DONE
"Invalid character in map" => DONE
"Map has more than one player" => DONE
"Invalid RGB value (min: 0, max: 255)"
"Missing texture(s)" => DONE
"Invalid texture(s)"
"Missing color(s)"
"Missing map" => DONE but i wrote Map is empty.
"Map is not at least 3 lines high" => Explanation ?
"Map is not surrounded by walls"
"Map is not the last element in file"
"Invalid player position"
"Map has no player position (expected N, S, E ou W)" => DONE
"Could not allocate memory" => OK
"Could not start mlx" => OK
"Could not create mlx window" => OK
"Could not create mlx image"

*/
