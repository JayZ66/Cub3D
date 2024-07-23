/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:02:21 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 13:02:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	create_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx, game->texture_paths[i], &game->textures[i].width, &game->textures[i].height);
		if (!game->textures[i].img)
		{
			printf("Could not create mlx image\n");
			free_all2(game);
		}
		game->textures[i].addr = (int *)mlx_get_data_addr(game->textures[i].img, &game->textures[i].pixel_bits, &game->textures[i].size_line, &game->textures[i].endian);
		i++;
	}
}

void	create_window(t_game *game)
{
	if (game->mlx == NULL)
	{
		printf("Mlx has not been set up \n");
		return ;
	}
	game->win = mlx_new_window(game->mlx, 500, 500,
			"Cub3d - A portail's world");
	if (!game->win)
	{
		printf("Could not create mlx window\n");
		return ;
	}
	// FILL THE WINDOW !
	// mlx_hook(game->win, KeyPress, KeyPressMask, &manage_keypress, game); // Manage Keypress
	mlx_hook(game->win, 17, KeyPressMask, &free_all2, game);
	mlx_loop(game->mlx);
}

// Init structures
// Create map
// Check map errors
int	main(int argc, char *argv[])
{
	t_game	game;
	char	*map;

	if (argc != 2)
		return (printf("Wrong nb of arguments\n"), 1);
	// game.win = NULL;
	map = ft_strdup(argv[1]);
	if (map == NULL)
		return (printf("There is no map\n"), 1);
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		printf("Could not start mlx\n");
		exit(EXIT_FAILURE);
	}
	init_cub(&game);
	// create_images(&game);
	read_map(&game, map);
	malloc_map(&game);
	fill_map(&game, map);
	manage_errors(&game, map);
	create_window(&game);
	// game.win = NULL;
	mlx_loop(game.mlx);
	free(map);
	free_all2(&game);
	return (0);
}
