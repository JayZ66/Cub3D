
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
				// game->player.dir_x = ; // si NO on met 0 ou autre (voir ENUM).
				game->player.dir_y = 1; // TO DO : protection pour le retournement !!
				player++;
			}
			j++;
		}
		i++;
	}
	printf("dir_x : %f\n", game->player.dir_x);
	printf("dir_y : %f\n", game->player.dir_y);
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
			return (printf("Walls are missing at the up side of the map\n"), 1);
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
// Check lignes vides
// Debut de la map : Ligne vide puis aucun char diff. de 11111 !
