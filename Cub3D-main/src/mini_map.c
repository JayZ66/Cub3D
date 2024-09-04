/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:51:45 by jeguerin          #+#    #+#             */
/*   Updated: 2024/09/04 16:30:51 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	draw_pixel(t_texture *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = (char *)img->addr + (y * img->size_line + x
				* (img->pixel_bits / 8));
		*(unsigned int *)dst = color;
	}
}

void	draw_mini_map_player(t_game *game)
{
	int	i;
	int	j;
	int	player_size;

	player_size = 6;
	i = -player_size / 2;
	while (i <= player_size / 2)
	{
		j = -player_size / 2;
		while (j <= player_size / 2)
		{
			draw_pixel(&game->mini_map, game->mini_map.width / 2 + i,
				game->mini_map.height / 2 + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

// `is_wall` function to treat portals as walls
int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map.width || map_y < 0 || map_y >= game->map.height)
		return 1; // Out of bounds treated as a wall
	// Check if it's a wall
	if (game->map.map[map_y][map_x] == '1' || game->map.map[map_y][map_x] == '2' || game->map.map[map_y][map_x] == '3')
		return (1); // Wall or Portal acts as a wall
	// Check if it's a door and player is near
	if (game->map.map[map_y][map_x] == 'D') {
		if (fabs(game->player.x - map_x) < 1.0 && fabs(game->player.y - map_y) < 1.0)
			return (1); // Treat door as wall if player is near
	}
	return (0); // No wall
}

void	draw(t_texture *img, int x, int y, int color)
{
	int		i;
	int		j;
	double	pixel_x;
	double	pixel_y;

	i = 0;
	while (i < T_SIZE)
	{
		j = 0;
		while (j < T_SIZE)
		{
			pixel_x = x * T_SIZE + j;
			pixel_y = y * T_SIZE + i;
			if (pixel_x < img->width && pixel_y < img->height)
				my_mlx_pixel_put(img, (int)pixel_x, (int)pixel_y, color);
			j++;
		}
		i++;
	}
}
