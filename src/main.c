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

/* CREATE WINDOW
	3. Fill_Window with assets
		a. Big loop to iterate on lines
		b. Small loop to iterate on columns
		c. Conditions depending on the letter/nb on the map.
			Use of mlx_put_image_to_window => NOT HERE NO ?
*/

// void	create_images(t_game *game)
// {

// }

void	create_window(t_game *game)
{
	if (game->mlx == NULL)
	{
		printf("Mlx has not been set up \n");
		return ;
	} // Why are we using win_heigth et pas juste les autres dans struct. map ?
	game->win = mlx_new_window(game->mlx, 500, 500, "Cub3d - A portail's world");
	if (!game->win)
	{
		printf("Could not create mlx window\n");
		return ;
	}
	// FILL THE WINDOW !
	// mlx_hook(game->win, KeyPress, KeyPressMask, &manage_keypress, game);
	mlx_hook(game->win, 17, KeyPressMask, &free_all2, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	char	*map;

	if (argc != 2)
		return (printf("Wrong nb of arguments\n"), 1);
	game.win = NULL;
	map = ft_strdup(argv[1]);
	if (map == NULL)
		return (printf("There is no map\n"), 1);
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		printf("Could not start mlx\n");
		exit(EXIT_FAILURE);
	}
	init_game(&game); // Init toutes les variables !
	// Create map
	read_map(&game, map);
	malloc_map(&game);
	fill_map(&game, map);
	// Check map errors
	manage_errors(&game, map);
	// Init structures
	create_window(&game);
	game.win = NULL;
	mlx_loop(game.mlx);
	free_all2(&game);
	free(map);
	return (0);
}
