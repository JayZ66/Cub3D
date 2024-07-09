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
	1. Check if mlx is null
	2. Use mlx_new_window
		a. params : mlx, largeur * 32 (nb de pixels ?),
		hauteur * 32, Name of the window.
		b. Check if win is null
		c. Fonction qui remplit la window
		d. Use of : 
			mlx_hook(win, KeyPress, KeyPressMask, &manage_keypress, struct);
			To close win : mlx_hook(win, KeyPressMask, add. of function that free, struct);
			mlx_loop(mlx);
	3. Fill_Window with assets
		a. Big loop to iterate on lines
		b. Small loop to iterate on columns
		c. Conditions depending on the letter/nb on the map.
			Use of mlx_put_image_to_window => NOT HERE NO ?

*/

// void	create_images(t_game *game)
// {

// }

int	free_all2(t_game *game)
{
	int	i;

	i = 0;
	printf("OK free \n");
	while (game->texture_paths[i])
	{
		free(game->texture_paths[i]);
		i++;
	}
	if (game->win != NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		exit(0);
	}
	return (0);
}

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
	const char	*map;

	if (argc != 2)
		return (printf("Wrong nb of arguments\n"), 1);
	map = ft_strdup(argv[1]); // Don't forget to free !
	if (map == NULL)
		return (printf("There is no map\n"), 1);
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		printf("Could not start mlx\n");
		exit(EXIT_FAILURE);
	}
	mlx_loop(game.mlx);
	// Create map
	read_map(&game, map);
	malloc_map(&game);
	fill_map(&game, map);
	// Check map errors
	manage_errors(&game, map);
	// Init structures
	create_window(&game);
	game.win = NULL;
}
