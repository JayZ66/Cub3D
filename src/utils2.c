/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:52:19 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/29 17:15:11 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/*
TO FREE : 
- mlx => DONE
- Win => DONE
- game->map.map
- game->portal_gun.img => DONE
- game->mini_map.img => DONE
- game->game->ball[2].texture.img => DONE
=> mlx_destroy_image(game->mlx, game->ball[0].texture.img)
- map du main
- 
*/

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture_paths[i])
			free(game->texture_paths[i]);
		i++;
	}
	if (game->ball[0].texture.img)
        mlx_destroy_image(game->mlx, game->ball[0].texture.img);
	if (game->ball[1].texture.img)
        mlx_destroy_image(game->mlx, game->ball[1].texture.img);
	if (game->portal_gun.img)
		mlx_destroy_image(game->mlx, game->portal_gun.img);
	if (game->mini_map.img)
		mlx_destroy_image(game->mlx, game->mini_map.img);
}

// game->texture_paths && game->texture_paths[i]
void	free_everything(t_game *game)
{
	if (game->win != NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

// printf("Line %s\n", game->map.map[i]);
// for (i = 0; i < 4; i++)
// {
//     if (game->textures[i].img)
//         mlx_destroy_image(game->mlx, game->textures[i].img);
// }
// if (game->portal_gun.img)
//     mlx_destroy_image(game->mlx, game->portal_gun.img);
int	free_all2(t_game *game)
{
	int	i;

	printf("OK free \n");
	mlx_do_key_autorepeatoff(game->mlx);
	if (game->map.map)
	{
		i = 0;
		while (game->map.map[i])
		{
			free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
	}
	free_textures(game);
	free_everything(game);
	exit(EXIT_SUCCESS);
	return (0);
}

int	check_char(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	only_space2(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r')
			return (0);
		line++;
	}
	return (1);
}

int	only_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
