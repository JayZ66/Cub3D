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
	game->win_height = 0;
	game->win_width = 0;
	memset(game->texture_paths, 0, sizeof(game->texture_paths));
	game->map.map = NULL;
	game->running = 1;
}

void	init_map(t_map *map)
{
	map->map = NULL;
	map->height = 0;
	map->width = 0;
}

void	init_cub(t_game *game)
{
	init_game(game);
	init_player(&game->player);
	init_color(&game->floor);
	init_color(&game->ceiling);
	init_texture(game->textures);
	init_map(&game->map);
	init_input(&game->input);
}
