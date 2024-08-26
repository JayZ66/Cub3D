
#include "../../cub3D.h"

void    load_portal_gun(t_game *game)
{
    game->portal_gun.width = 64;
	game->portal_gun.height = 64;
	game->gun_shot = 0;
	game->shot_frame = 0;
	game->portal_gun.img = mlx_xpm_file_to_image(game->mlx, "src/sprites/images/gun.xpm", &game->portal_gun.width, &game->portal_gun.height);
    if (!game->portal_gun.img)
    {
		printf("Failed to load portal gun texture\n");
		free_all2(game);
    }
	game->portal_gun.addr = (int *)mlx_get_data_addr(game->portal_gun.img, &game->portal_gun.pixel_bits, &game->portal_gun.size_line, &game->portal_gun.endian);
	if (!game->portal_gun.addr)
    {
		printf("Failed to load portal gun address\n");
		mlx_destroy_image(game->mlx, game->portal_gun.img);
		free_all2(game);
    }
}

void	display_portal_gun(t_game *game)
{
	int	x;
	int	y;

	 if (!game->mlx || !game->win || !game->portal_gun.img) // Vérifiez si l'image est valide
    {
        printf("Portal gun image is not loaded.\n");
        return;
    }
	x = (game->win_width - game->portal_gun.width) / 2;
	y = game->win_height - game->portal_gun.height - 20; // 20 px au-dessus du bas de l'écran.
	if (game->gun_shot == 1) // Simuler le recul lors du tire avec l'arme.
	{
		y += 10;
		game->shot_frame++;
		if (game->shot_frame > 5) // Limiter la durée de l'animation.
		{
			game->gun_shot = 0;
			game->shot_frame = 0;
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->portal_gun.img, x, y);
 }