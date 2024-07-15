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
	while ((line = get_next_line(fd)) != NULL)
	{
		// Si ligne vide => je break la boucle
		// printf("Height: %d\n", game->map.height);
		// Check par ordre des lignes donc ligne X est ca.
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
	memset(game->texture_paths, 0, sizeof(game->texture_paths));
	while (1) // CHECK IF AU MOINS LIGNE DE VIDE AVEC UN FLAG!!!
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (textures != 4 && is_path_textures(game, line) == 0)
			textures += 1;
		else if (rgb != 2 && is_rgb_code(game, line) == 0)
			rgb += 1;
		else if ((check_char(line, '1') == 1 || check_char(line, '0') == 1)
			&& (check_char(line, 'F') == 0 && check_char(line, 'C') == 0)) // Pas bon car va me mettre les lignes avec espaces et tout !
		{
			if (i >= game->map.height)
			{
				printf("Error: map height exceeded allocated space\n");
				break ;
			}
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
=> Should we manage the error or could be a space ? Yes !
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
	*g = ft_atoi2(line);
	if (*g == -1)
		return (printf("Green color code is missing\n"), 1);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
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
		free_all2(game);
	}
	return (1);
}

// Checker si 2 fois même texture !
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
		return (1);
	}
	return (0);
}

int	is_file_extension_valid(const char *file)
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

int	is_map_empty(t_game *game)
{
	size_t	i;
	int		empty_map;

	i = 0;
	empty_map = 0;
	while (game->map.map[i])
	{
		if (game->map.map[i] == NULL)
			empty_map++;
		i++;
	}
	if (empty_map == game->map.height)
	{
		printf("Empty : %d\n", empty_map);
		printf("Map is empty\n");
		return (1);
	}
	return (0);
}

int	is_file_empty(const char *file, t_game *game)
{
	int		fd;
	char	c;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	if (read(fd, &c, 1) == 0)
	{
		printf("File is empty\n");
		close(fd);
		free_all2(game);
	}
	close(fd);
	return (0);
}

// printf("Map : %c\n", game->map.map[i][j]);
// printf("Map : %s\n", game->map.map[i]);
int	is_player_valid(t_game *game)
{
	size_t	i;
	size_t	j;
	int		player;

	i = 0;
	player = 0;
	while (game->map.map[i])
	{
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S'
				|| game->map.map[i][j] == 'W' || game->map.map[i][j] == 'E')
			{
				game->player.x = j;
				game->player.y = i;
				player++;
			}
			j++;
		}
		i++;
	}
	if (player > 1)
		return (printf("Map has more than one player\n"), 1);
	else if (player == 0)
		return (printf("Map has no player position (N, S, E, W)\n"), 1);
	return (0);
}

int	is_char_valid(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.map[i][j] != '1' && game->map.map[i][j] != '0'
				&& game->map.map[i][j] != 'S' && game->map.map[i][j] != 'N'
				&& game->map.map[i][j] != 'W' && game->map.map[i][j] != 'E'
				&& game->map.map[i][j] != 32 && game->map.map[i][j] != '\0'
				&& game->map.map[i][j] != '\n')
			{
				printf("Invalid character in map\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

// ASK : Walls check square form or the check adapts itself 
// to the shape of the map ?
// ligne y / colonne x
// Il faut : check tant que ligne à position 0 n'est pas égale à 
// 1 on avance de y.

int	are_walls_valid(t_game *game)
{
	int		i;
	int		j;
	int		width;
	char	*line;

	// Check top line of the map
	line = game->map.map[0];
	width = ft_strlen(line);
	j = 0;
	while (j < width)
	{
		i = 0;
		while (i < game->map.height && (game->map.map[i][j] == ' '
			|| game->map.map[i][j] == '\n'))
		{
			printf("LINE : %c\n", line[j]);
			i++;
		}
		printf("LINE : %c\n", line[j]);
		if (i < game->map.height && game->map.map[i][j] != '1')
			return (printf("Walls are missing at the up side of the map\n", 1));
		j++;
	}
	//Check bottom line of the map
	line = game->map.map[game->map.height - 1];
	width = ft_strlen(line);
	j = 0;
	while (j < width)
	{
		i = game->map.height - 1;
		while (i >= 0 && (game->map.map[i][j] == ' '
			|| game->map.map[i][j] == '\n'))
		{
			printf("LINE : %c\n", line[j]);
			i--;
		}
		printf("LINE : %c\n", line[j]);
		if (i >= 0 && game->map.map[i][j] != '1')
			return (printf("Walls are missing at the bottom side of the map\n")
				, 1);
		j++;
	}
	//Check left & right of the map.
	i = 0;
	while (i < game->map.height)
	{
		line = game->map.map[i];
		width = ft_strlen(line);
		//Vérifier le premier caractère de la ligne (bord gauche)
		j = 0;
		while (line[j] == ' ' || line[j] == '\n')
			j++;
		if (line[j] != '1')
			return (printf("Walls are missing at the left side of the map\n")
				, 1);
		//Vérifier le dernier caractère de la ligne (bord droit)
		j = width - 1;
		while (j >= 0 && (line[j] == ' ' || line[j] == '\n'))
			j--;
		if (j >= 0 && line[j] != '1')
			return (printf("Walls are missing at the right side of the map\n")
				, 1);
		i++;
	}
	return (0);
}

// int are_walls_valid(t_game *game)
// {
//     int i;

//     i = 0;
//     // En haut
//     while (i < game->map.width - 1)
//     {
// 		printf("LINE up : %c\n", game->map.map[0][i]);
// 		while (game->map.map[0][i] == 32)
// 			i++;
//         if (game->map.map[0][i] != '1' && game->map.map[0][i] != '\n'
// 			&& game->map.map[game->map.height - 1][i] != 32)
//             return (printf("Walls are missing at the top of the map\n"), 1);
//         i++;
//     }
//     // En bas
//     i = 0;
//     while (game->map.map[game->map.height - 1][i])
//     {
// 		printf("LINE bottom : %c\n", game->map.map[game->map.height - 1][i]);
//         if (game->map.map[game->map.height - 1][i] != '1'
//			&& game->map.map[game->map.height - 1][i] != '\n'
// 			&& game->map.map[game->map.height - 1][i] != 32)
//         	return (printf("Walls are missing at the bottom of the map\n"), 1);
//         i++;
//     }
//     // A gauche
//     i = 0;
//     while (i < game->map.height - 1)
//     {
// 		printf("LINE left: %c\n", game->map.map[i][0]);
// 		while (game->map.map[i][0] == 32)
// 			i++;
//         if (game->map.map[i][0] != '1' && game->map.map[i][0] != 32)
//         	return (printf("Walls are missing at the left of the map\n"), 1);
//         // if (game->map.map[i][game->map.width - 1] != '1'
//				&& game->map.map[i][game->map.width - 1] != '\n'
//         //         && game->map.map[i][game->map.width - 1] != '\0'
//						&& game->map.map[game->map.height - 1][i] != 32)
//         // 	return (printf("Walls are missing at the right of the map\n")
//						, 1);
//         i++;
//     }
// 	// A droite
// 	i = 0;
// 	while (game->map.map[i][game->map.width - 1])
// 	{
// 		while (game->map.map[i][game->map.width - 1] == 32)
// 			i++;
// 		printf("LINE right: %c\n", game->map.map[i][game->map.width - 1]);
// 		 if (game->map.map[i][game->map.width - 1] != '1'
//			&& game->map.map[i][game->map.width - 1] != '\n'
//          && game->map.map[i][game->map.width - 1] != '\0'
//			&& game->map.map[i][game->map.width - 1] != 32) // To check
//         	return (printf("Walls are missing at the right of the map\n"), 1);
// 		i++;
// 	}
//     return (0);
// }

int	is_map_valid(t_game *game)
{
	// Map with \n => Is that ok ? Bce of fill_map.
	if (is_map_empty(game) == 1)
		return (1);
	// Allowed character in map
	if (is_char_valid(game) == 1)
		return (1);
	// Map has no player position or too many in the map
	if (is_player_valid(game) == 1)
		return (1);
	// Map surrounded by walls only
	if (are_walls_valid(game) == 1)
		return (1);
	return (0);
}
// Invalid player position => What does it mean ?
// (outside walls or blocked ?)
// Check lignes vides
// Debut de la map : Ligne vide puis aucun char diff. de 11111 !

/*
Check si une ligne vide puis wall puis wallpuis vide et si apres pas bon !
*/
int	is_file_full(const char *file, t_game *game)
{
	int		fd;
	int		check;
	char	*line;

	check = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line  == NULL)
			break ;
		if (ft_strncmp_cub(line, '1', ft_strlen(line)) == 0)
			check++;
		if (check == 2 && line != NULL && *line != '\n')
		{
			printf("Map is not the last element in file\n");
			return (1);
		}
	}
	return (0);
}

int	is_file_valid(const char *file, t_game *game)
{
	// File extension
	if (is_file_extension_valid(file) == 1)
		return (1);
	// Empty file
	if (is_file_empty(file, game) == 1) // Check if file empty ?
		return (1);
	return (0);
}
// Missing colors => DONE
// Map is not the last element in the file
// CHECK TEXTURES && RGB EN DOUBLE

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
