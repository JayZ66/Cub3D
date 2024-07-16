/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:57:03 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 13:57:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
}

void	init_game(t_game *game)
{
	game->win = NULL;
	game->map.map = NULL;
	game->win_height = 0;
	game->win_width = 0;
	memset(game->texture_paths, 0, sizeof(game->texture_paths));
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->height = 0;
	map->width = 0;
}

void	init_color(t_color *color)
{
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

void	init_texture(t_texture *texture)
{
	texture->img = NULL;
	texture->addr = NULL;
	texture->pixel_bits = 0;
	texture->size_line = 0;
	texture->endian = 0;
	texture->width = 0;
	texture->height = 0;
}

void	init_cub(t_game *game)
{
	init_game(game);
	init_player(&game->player);
	init_color(&game->floor);
	init_color(&game->ceiling);
	init_texture(game->textures);
	init_map(&game->map);
}
