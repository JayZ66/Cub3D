/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:54:27 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/29 18:30:11 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// void	check_map_path(double x, double y, t_game *game)
// {
// 	if (game->map.map[y][x] != '1')
// 	{
// 		mlx_put_image_to_window(game->mlx, game->win, game->floor.b, game->player.x, game->player.y);
// 		game->player.x = x;
// 		game->player.y = y;
// 		mlx_put_image_to_window(game->mlx, game->win, game->ceiling.r, game->player.x, game->player.y);
// 	}
// }

// If i press w key i'll get many moves, at a time, but then it'll be outside the map.
int	is_outside(t_game *game, double x, double y)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = (int)x;
	tmp_y = (int)y;
	// printf("Tmp-x : %d\n", tmp_x);
	// printf("Width : %d\n", game->map.width);
	// printf("Height : %d\n", game->map.height);
	if (tmp_x >= 0 && tmp_x < game->map.width && tmp_y >= 0 && tmp_y < game->map.height)
		return (0);
	return (1);
}

void	update_position(t_game *game, double x, double y)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = game->player.x + x;
	tmp_y = game->player.y + y;
	printf("Position x : %f\n", game->player.x);
	printf("Position y : %f\n", game->player.y);
	if (is_outside(game, tmp_x, tmp_y) == 0)
	{
		game->player.x = tmp_x;
		game->player.y = tmp_y;
	}
	else
		free_all2(game);
	printf("New position x : %f\n", game->player.x);
	printf("New position y : %f\n", game->player.y);
	// if pas de collision pour le nouveau x
		// on attribue la nouvelle valeur a x
	// If pas de collision pour le nouveau y
		// on attribue la nouvelle valeur a y
}

// void    move_forward(t_game *game)
// {
//     double	tmp_x;
//     double	tmp_y;

// 	tmp_x = game->player.x;
// 	tmp_y = game->player.y;
// 	tmp_y--;
// 	if (tmp_x >= 0 && tmp_x < game->map.width && tmp_y >= 0 && tmp_y < game->map.height)
// 		check_map_path();
// }