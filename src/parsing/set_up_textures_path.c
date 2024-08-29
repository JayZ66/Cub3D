/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_textures_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:48:02 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/29 14:50:50 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	invalid_texture(t_game *game)
{
	printf("Invalid texture(s) - doublon\n");
	free_all2(game);
}

void	north_path(t_game *game, char *line)
{
	if (game->texture_paths[NORTH] == NULL)
		game->texture_paths[NORTH] = ft_strdup(line + 3);
	else
		invalid_texture(game);
}

void	south_path(t_game *game, char *line)
{
	if (game->texture_paths[SOUTH] == NULL)
		game->texture_paths[SOUTH] = ft_strdup(line + 3);
	else
		invalid_texture(game);
}

void	west_path(t_game *game, char *line)
{
	if (game->texture_paths[WEST] == NULL)
		game->texture_paths[WEST] = ft_strdup(line + 3);
	else
		invalid_texture(game);
}

void	east_path(t_game *game, char *line)
{
	if (game->texture_paths[EAST] == NULL)
		game->texture_paths[EAST] = ft_strdup(line + 3);
	else
		invalid_texture(game);
}
