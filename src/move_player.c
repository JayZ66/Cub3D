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
// 		mlx_put_image_to_window(game->mlx, game->win, game->floor.b,
//			game->player.x, game->player.y);
// 		game->player.x = x;
// 		game->player.y = y;
// 		mlx_put_image_to_window(game->mlx, game->win, game->ceiling.r,
//			game->player.x, game->player.y);
// 	}
// }

// printf("Map-x : %d\n", map_x);
	// printf("Width : %d\n", game->map.width);
	// printf("Height : %d\n", game->map.height);
int	is_outside(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map.width || map_y < 0
		|| map_y >= game->map.height)
		return (1);
	if (game->map.map[map_y][map_x] == ' '
		|| game->map.map[map_y][map_x] == '1')
		return (1);
	return (0);
}

// if pas de collision pour le nouveau x
		// on attribue la nouvelle valeur a x
	// If pas de collision pour le nouveau y
		// on attribue la nouvelle valeur a y

// void	update_position(t_game *game, double move_x, double move_y)
// {
// 	double	new_x;
// 	double	new_y;

// 	new_x = game->player.x + move_x;
// 	new_y = game->player.y + move_y;
// 	if (!is_outside(game, new_x, new_y))
// 	{
// 		game->player.x = new_x;
// 		game->player.y = new_y;
// 	}
// 	else
// 	{
// 		if (!is_outside(game, new_x, game->player.y))
// 			game->player.x = new_x;
// 		if (!is_outside(game, game->player.x, new_y))
// 			game->player.y = new_y;
// 	}
// 	printf("New position x : %f\n", game->player.x);
// 	printf("New position y : %f\n", game->player.y);
// }

void	update_position(t_game *game, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + move_x * game->player.speed;
	new_y = game->player.y + move_y * game->player.speed;
	if (!is_outside(game, new_x, new_y))
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
	else
	{
		if (!is_outside(game, new_x, game->player.y))
			game->player.x = new_x;
		if (!is_outside(game, game->player.x, new_y))
			game->player.y = new_y;
	}
	printf("New position x : %f\n", game->player.x);
	printf("New position y : %f\n", game->player.y);
}

// printf("Before rotation:\n");
	// printf("Direction: dir_x = %f, dir_y = %f\n", game->player.dir_x,
	//	game->player.dir_y);
	// printf("Plane: plane_x = %f, plane_y = %f\n", game->player.plane_x,
	//	game->player.plane_y);

// void	rotate_player(t_game *game, double angle)
// {
// 	double	old_dir_x;
// 	double	old_dir_y;
// 	double	old_plane_x;
// 	double	old_plane_y;

// 	old_dir_x = game->player.dir_x;
// 	old_dir_y = game->player.dir_y;
// 	old_plane_x = game->player.plane_x;
// 	old_plane_y = game->player.plane_y;
// 	angle *= game->player.rot_speed;
// 	game->player.dir_x = old_dir_x * cos(angle) - old_dir_y * sin(angle);
// 	game->player.dir_y = old_dir_x * sin(angle) + old_dir_y * cos(angle);
// 	game->player.plane_x = old_plane_x * cos(angle) - old_plane_y * sin(angle);
// 	game->player.plane_y = old_plane_x * sin(angle) + old_plane_y * cos(angle);
// }
// 	printf("After rotation:\n");
//     printf("Direction: dir_x = %f, dir_y = %f\n", game->player.dir_x,
//		game->player.dir_y);
//     printf("Plane: plane_x = %f, plane_y = %f\n", game->player.plane_x,
//		game->player.plane_y);

void	rotate_player(t_game *game, int direction)
{
    double old_dir_x;
    double old_plane_x;
    double rotation_speed;

    old_dir_x = game->player.dir_x;
    old_plane_x = game->player.plane_x;
    rotation_speed = direction * game->player.rot_speed
    game->player.dir_x = game->player.dir_x * cos(rotation_speed) - game->player.dir_y * sin(rotation_speed);
    game->player.dir_y = old_dir_x * sin(rotation_speed) + game->player.dir_y * cos(rotation_speed);
    game->player.plane_x = game->player.plane_x * cos(rotation_speed) - game->player.plane_y * sin(rotation_speed);
    game->player.plane_y = old_plane_x * sin(rotation_speed) + game->player.plane_y * cos(rotation_speed);
}

int	render_frame(t_game *game)
{
	t_texture frame;

	frame.width = game->win_width;
	frame.height = game->win_height;
	frame.img = mlx_new_image(game->mlx, frame.width, frame.height);
	frame.addr = (int *)mlx_get_data_addr(frame.img, &frame.pixel_bits, &frame.size_line, &frame.endian);
	render_mini_map(game, &frame);
	mlx_put_image_to_window(game->mlx, game->win, frame.img, 0, 0);
	mlx_destroy_image(game->mlx, frame.img);
	is_action(game);
	return (0);
}
