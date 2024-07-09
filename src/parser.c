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
		b. Loop to fill our map. On malloc que le contenu et plus la map dans son ensemble !
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

void	read_map(t_game *game, const char *file) // Which variable is the file (in struct. or not) ?
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		// game->map.map = NULL;
		printf("Could not open the map file\n");
		free_all2(game);
	}
	game->map.height = 0; // Check if we initialize it here ?
	game->map.width = 0; // + Size of the map not the win right ?
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (line[0] == '0' || line[1] == '1') // How to handle if the map is not a square ?
		{
			if (game->map.height == 0)
				game->map.width = ft_strlen(line) - 1; // See if it's good as map is not always a square.
			game->map.height++;
		}
		free(line);
	}
	close(fd);
}

void	malloc_map(t_game *game)
{
	game->map.map = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.map)
	{
		printf("Could not allocate memory\n");
		return ;
	}
	game->map.map[game->map.height] = NULL;
}

void	fill_map(t_game *game, const char *file)
{
	size_t	i;
	int		fd;
	int 	textures;
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
	memset(game->texture_paths, 0, sizeof(game->texture_paths)); // Init. tab with 0.
	while (1)
	{
		line = get_next_line(fd);
		printf("Line : %s\n", line);
		if (line == NULL)
			break ;
		if (ft_isspace(line))
			continue ;
		if (textures != 4 && is_path_textures(game, line) == 0)
		{
			textures += 1;
			continue ;
		}
		else if (rgb != 2 && is_rgb_code(game, line) == 0)
		{
			rbg += 1;
			continue ;
		}
		else // Pas bon car va me mettre les lignes avec espaces et tout !
			game->map.map[i] = ft_strdup(line);
		i++;
		free(line);
	}
	close(fd);
	// printf("Texture : %s\n", game->texture_paths[1]);
	// i = 0;
	// while (game->map.map[i])
	// {
	// 	printf("LINE : %s\n", game->map.map[i]);
	// 	i++;
	// }
}

int	parse_rgb(char *line, int *r, int *g, int *b)
{
	*r = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',') // Should we manage the error or could be a space ?
		line++;
	*g = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	*b = ft_atoi(line);
	while (ft_isdigit(*line))
		line++;
	if (*line != '\0') //  && !isspace(*line) - Should we check the end of the line ?
		return (1);
	if (*r <= 0 || *r >= 255 || *g <= 0 || *r >= 255 || *b <= 0 || *b >= 255)
		return (1);
	return (0);
}

// Ligne 5 only authorize (\t \n ' ' ect...) // How to check it with gnl ?
// F int,int,int (compris entre 0 et 255)
// C ligne 8 only authorize (\t \n ' ' ect...) 
// AP (a partir de la rien dautoriser hors ' ' 1 0) fin de la map quand une ligne commence par \n,
// apres cela aucun char autoriser hors \n
int	is_rgb_code(t_game *game, char *line)
{
	// int	i;
	int		r;
	int		g;
	int		b;
	char	*rgb_line;

	// i = 0;
	// printf("Line : %s\n", line);
	if ((line[0] == 'C' || line[0] == 'F') && line[1] == ' ')
	{
		rgb_line = line + 2;
		if (parse_rgb(rgb_line, &r, &g, &b) != 0)
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
	else
	{
		printf("Invalid id for RGB color\n");
		free_all2(game);
	}
	return (1);
}

int	ft_isspace(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] < 9 || line[i] > 13 || line[i] != 32)
			return (1);
		i++;
	}
	return (0);
}

int	is_path_textures(t_game *game, char *line)
{
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
	else
	{
		printf("Missing texture(s)\n");
		free_all2(game);
	}
	return (0);
}

int	is_file_valid(const char *file)
{
	int	start_position;
	int	extension;
	int	size;

	size = ft_strlen(file);
	extension = ft_strlen(".cub");
	start_position = size - extension;
	if (start_position < 0 || ft_strcmp(file + start_position, ".cub") != 0)
	{
		printf("Not a .cub file\n");
		return (1);
	}
	return (0);
}

// int	is_file_content_valid(const char *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (game->map.map[i])
// 	{
// 		j = 0;
// 		while (game->map.map[i][j])
// 		{
			
// 		}
// 	}
// }

void	manage_errors(t_game *game, const char *file)
{
	if (is_file_valid(file) == 1)
		free_all2(game);
	// if (is_file_content_valid(file) == 1)
	// 	free_all2(game);
}

/* ERRORS TO HANDLE
Errors map : 
Validiter du fichier .cub => DONE
1er ligne start avec NO puis un ' ' puis save toute la ligne jusquau '\n' => DONE
SO pareil => DONE
WE pareil => DONE
EA pareil => DONE
ligne 5 only authorize (\t \n ' ' ect...)
F int,int,int (compris entre 0 et 255) => DONE
C ligne 8 only authorize (\t \n ' ' ect...) => DONE
AP (a partir de la rien dautoriser hors ' ' 1 0) fin de la map quand une ligne commence par \n,
apres cela aucun char autoriser hors \n


Message a afficher en cas de probleme d'input :

Il manque North/South/East/West/Floor/Ceiling/Map pour accepter la map

Manque un espace entre North/South/East/West/Floor/Ceiling et leur valeur

Path invalide pour North/South/East/West

Valeur RGB invalide pour Floor/Ceiling

Manque une ligne vide entre les textures et les couleurs (ligne 5)

Manque une ligne vide entre les couleurs et la map (ligne 8)

Map invalide, Char interdit dans la map ( /1/0)

Map invalide, la map doit etre entourer de mur (tips sur lalgo de graph)

Aucun char autoriser apres la fin de la map (apres une premiere ligne vide post map)

*/

/* ERRORS TO HANDLE
Voici un exemple de toutes les erreurs qui doivent être traitées dans le ticket parsing ou init :

"Not a .cub file" => OK
"Not an .xpm file"
"Invalid floor/ceiling RGB color(s)" => DONE
"Invalid floor RGB color" => DONE
"Invalid ceiling RGB color" => DONE
"Map description is either wrong or incomplete"
"Invalid character in map"
"Map has more than one player"
"Invalid RGB value (min: 0, max: 255)"
"Missing texture(s)" => DONE
"Invalid texture(s)"
"Missing color(s)"
"Missing map"
"Map is not at least 3 lines high"
"Map is not surrounded by walls"
"Map is not the last element in file"
"Invalid player position"
"Map has no player position (expected N, S, E ou W)"
"Could not allocate memory" => OK
"Could not start mlx" => OK
"Could not create mlx window" => OK
"Could not create mlx image"

*/
