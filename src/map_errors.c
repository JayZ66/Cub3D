/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:00 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/23 17:26:02 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

// printf("Map : %c\n", game->map.map[i][j]);
// printf("Map : %s\n", game->map.map[i]);
// game->player.dir_y = 1; // TO DO : protection pour le retournement !!
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
				if (game->map.map[i][j] == 'N')
					game->player.dir_x = 0;
				else if (game->map.map[i][j] == 'E')
					game->player.dir_x = 1;
				else if (game->map.map[i][j] == 'W')
					game->player.dir_x = 2;
				else if (game->map.map[i][j] == 'S')
					game->player.dir_x = 3;
				game->player.dir_y = 1;
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

// ligne y / colonne x
// printf("Height : %d\n", game->map.height);
// printf("Width : %d\n", game->map.width);
int	flood_fill(t_game *game, char **map, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (0);
	if (map[y][x] == '0')
	{
		if ((y > 0 && map[y - 1][x] == ' ')
			|| (y < game->map.height - 1 && map[y + 1][x] == ' ')
			|| (x > 0 && map[y][x - 1] == ' ')
			|| (x < game->map.width - 1 && map[y][x + 1] == ' '))
			return (printf("X: %d\n", x), printf("Y: %d\n", y), 1);
	}
	map[y][x] = 'X';
	if (flood_fill(game, map, x - 1, y - 1) == 1
		|| flood_fill(game, map, x, y - 1) == 1
		|| flood_fill(game, map, x + 1, y - 1) == 1
		|| flood_fill(game, map, x - 1, y) == 1
		|| flood_fill(game, map, x + 1, y) == 1
		|| flood_fill(game, map, x - 1, y + 1) == 1
		|| flood_fill(game, map, x, y + 1) == 1
		|| flood_fill(game, map, x + 1, y + 1) == 1)
		return (1);
	return (0);
}
// Check diagonales aussi avec x + 1 / y + 1 et etc.
//         if (flood_fill(game, map, x - 1, y - 1) || // Haut-Gauche
//             flood_fill(game, map, x - 1, y) ||    // Haut
//             flood_fill(game, map, x - 1, y + 1) ||// Haut-Droite
//             flood_fill(game, map, x, y - 1) ||    // Gauche
//             flood_fill(game, map, x, y + 1) ||    // Droite
//             flood_fill(game, map, x + 1, y - 1) ||// Bas-Gauche
//             flood_fill(game, map, x + 1, y) ||    // Bas
//             flood_fill(game, map, x + 1, y + 1))  // Bas-Droite
//             return 1;

// int flood_fill(t_game *game, char **map, int x, int y)
// {
//     if (x < 0 || y < 0 || y >= game->map.height || x >= game->map.width)
//         return 1; // Hors limites
//     if (map[y][x] == '1' || map[y][x] == 'X')
//         return 0; // Case visitée ou mur
//     if (map[y][x] == '0')
//     {
//         if ((y > 0 && map[y - 1][x] == ' ') ||
//             (y < game->map.height - 1 && map[y + 1][x] == ' ') ||
//             (x > 0 && map[y][x - 1] == ' ') || // Case à gauche
//             (x < game->map.width - 1 && map[y][x + 1] == ' '))
//             return 1; // Contact avec un espace vide
//     }
//     map[y][x] = 'X';
//     if (flood_fill(game, map, y - 1, x) == 1 ||
//         flood_fill(game, map, y + 1, x) == 1 ||
//         flood_fill(game, map, y, x - 1) == 1 ||
//         flood_fill(game, map, y, x + 1) == 1)
//         return 1;
//     return 0;
// }

char	**get_map(t_game *game)
{
	int		i;
	char	**map;

	map = malloc(sizeof(char *) * (game->map.height + 1));
	if (!map)
		return (printf("Can't malloc the map\n"), NULL);
	i = 0;
	while (game->map.map[i])
	{
		map[i] = ft_strdup(game->map.map[i]);
		i++;
	}
	map[i] = NULL;
	i = 0;
	while (map[i])
	{
		printf("Map[i] : %s\n", map[i]);
		i++;
	}
	return (map);
}

int	are_walls_valid(t_game *game)
{
	char	**map;
	int		i;

	map = get_map(game);
	if (map == NULL)
		return (printf("Can't copy map\n"), 1);
	if (flood_fill(game, map, game->player.x, game->player.y) == 1)
		return (printf("Map is not surrounded by walls\n"), 1);
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (0);
}

// int are_walls_valid(t_game *game)
// {
//     char **map;
//     int i;

//     map = get_map(game);
//     if (map == NULL)
//         return (printf("Can't copy map\n"), 1);
//     for (i = 0; i < game->map.width; i++)
//     {
//         if (map[0][i] == ' ')
//             if (flood_fill(game, map, 0, i))
// 				return (printf("Map is not surrounded by walls\n"), 1);
//         if (map[game->map.height - 1][i] == ' ')
//             if (flood_fill(game, map, game->map.height - 1, i))
// 				return (printf("Map is not surrounded by walls\n"), 1);
//     }
//     for (i = 0; i < game->map.height; i++)
//     {
//         if (map[i][0] == ' ')
//             if (flood_fill(game, map, i, 0))
// 				return (printf("Map is not surrounded by walls\n"), 1);
//         if (map[i][game->map.width - 1] == ' ')
//             if (flood_fill(game, map, i, game->map.width - 1))
// 				return (printf("Map is not surrounded by walls\n"), 1);
//     }
//     i = 0;
//     while (map[i])
//     {
//         free(map[i]);
//         i++;
//     }
//     free(map);

//     return 0;
// }

int	is_map_valid(t_game *game)
{
	if (is_map_empty(game) == 1)
		return (1);
	if (is_char_valid(game) == 1)
		return (1);
	if (is_player_valid(game) == 1)
		return (1);
	if (are_walls_valid(game) == 1)
		return (1);
	return (0);
}
// Check lignes vides
// Debut de la map : Ligne vide puis aucun char diff. de 11111 !
