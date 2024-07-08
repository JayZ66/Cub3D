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
	1. Read map => In order to get the size (width / height)
		a. Check if empty map.
		b. Open file
		c. Loop to get the size of the map.
	2. Malloc the map
	3. Fill the map =>Same as the first step.
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

void	read_map(t_game *game, const char *file) // Which variable is the file ?
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		// game->map.map = NULL;
		printf("Could not open the map file\n");
		free_everything(game);
	}
	game->map.height = 0; // Check if we initialize it here ?
	game->map.width = 0; // + Size of the map not the win right ?
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (game->map.height == 0)
			game->map.width = ft_strlen(line) - 1; // See if it's good as map is not always a square.
		game->map.height++;
		free(line);
	}
	close(fd);
}

void	malloc_map(t_game *game)
{
	game->map.map = malloc(sizeof(char *) * (game->map.heigth + 1));
	if (!game->map.map)
	{
		printf("Could not allocate memory\n");
		return ;
	}
	game->map.map[game->map.height] = NULL;
}

/* ERRORS TO HANDLE
Erreuros map : 
Validiter du fichier .cub 1er ligne start avec NO puis un ' ' puis save toute la ligne jusquau '\n' SO pareil WE pareil EA pareil ligne 5 only authorize (\t \n ' ' ect...) F int,int,int (compris entre 0 et 255) C ligne 8 only authorize (\t \n ' ' ect...) MAP (a partir de la rien dautoriser hors ' ' 1 0) fin de la map quand une ligne commence par \n, apres cela aucun char autoriser hors \n

Message a afficher en cas de probleme d'input

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

"Not a .cub file"
"Not an .xpm file"
"Invalid floor/ceiling RGB color(s)"
"Invalid floor RGB color"
"Invalid ceiling RGB color"
"Map description is either wrong or incomplete"
"Invalid character in map"
"Map has more than one player"
"Invalid RGB value (min: 0, max: 255)"
"Missing texture(s)"
"Invalid texture(s)"
"Missing color(s)"
"Missing map"
"Map is not at least 3 lines high"
"Map is not surrounded by walls"
"Map is not the last element in file"
"Invalid player position"
"Map has no player position (expected N, S, E ou W)"
"Could not allocate memory"
"Could not start mlx"
"Could not create mlx window"
"Could not create mlx image"

*/
