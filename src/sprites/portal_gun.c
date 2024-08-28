/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_gun.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:37:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/27 19:43:07 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void    load_portal_gun(t_game *game)
{
    game->portal_gun.width = 64;
	game->portal_gun.height = 64;
	game->portal_gun.img = mlx_xpm_file_to_image(game->mlx, "src/sprites/sprites/portal_gun.xpm", &game->portal_gun.width, &game->portal_gun.height);
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

void merge_texture(t_texture *bg, t_texture *fg, t_game *game, int x, int y)
{
    int i, j;
    int fg_pixel, bg_pixel;
    int transparency_color = 0x000000;  // Noir comme couleur de transparence

    (void)bg_pixel;
    (void)game;
    for (j = 0; j < fg->height; j++)
    {
        for (i = 0; i < fg->width; i++)
        {
            fg_pixel = fg->addr[j * fg->size_line / 4 + i];  // Accès au pixel de fg
            if (fg_pixel != transparency_color)
            {
                bg_pixel = bg->addr[(y + j) * bg->size_line / 4 + (x + i)];
                bg->addr[(y + j) * bg->size_line / 4 + (x + i)] = fg_pixel;
            }
        }
    }
}

void overlay_texture(t_texture *fg, t_texture *bg, t_game *game, int x, int y)
{
    t_texture back;

    // Créer une image de fond (background) pour l'overlay
    back.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
    back.addr = (int *)mlx_get_data_addr(back.img, &back.pixel_bits, &back.size_line, &back.endian);
    back.width = game->win_width;
    back.height = game->win_height;
    back.pixel_bits = 32;
    back.size_line = back.width * (back.pixel_bits / 8);
    back.endian = 0;

    // Copier le fond dans l'image de fond
    memcpy(back.addr, bg->addr, back.size_line * back.height);

    // Fusionner les images
    merge_texture(&back, fg, game, x, y);

    // Afficher l'image combinée
    mlx_put_image_to_window(game->mlx, game->win, back.img, 0, 0);

    // Nettoyer les ressources
    mlx_destroy_image(game->mlx, back.img);
}

// void display_portal_gun(t_game *game)
// {
//     t_texture portal_gun;
//     int x, y;

//     // Vérifie si l'image du portal gun est chargée
//     if (!game->portal_gun.img)
//     {
//         printf("Portal gun image is not loaded.\n");
//         return;
//     }

//     // Initialise la texture du portal gun
//     portal_gun.img = game->portal_gun.img;
//     portal_gun.addr = (int *)mlx_get_data_addr(portal_gun.img, &portal_gun.pixel_bits, &portal_gun.size_line, &portal_gun.endian);
//     portal_gun.width = game->portal_gun.width;
//     portal_gun.height = game->portal_gun.height;
//     portal_gun.pixel_bits = 32;

//     // Position de l'image sur l'écran
//     x = (game->win_width - portal_gun.width) / 2;
//     y = game->win_height - portal_gun.height - 10;

//     // Vérifie si l'arme est tirée pour ajuster la position
//     if (game->gun_shot == 1)
//     {
//         y += 10;
//         game->shot_frame++;
//         if (game->shot_frame > 5)
//         {
//             game->gun_shot = 0;
//             game->shot_frame = 0;
//         }
//     }

//     // Afficher le portal gun avec transparence
//     overlay_texture(&portal_gun, &game->mini_map, game, x, y);
// }



// void display_portal_gun(t_game *game)
// {
//     t_texture portal_gun_texture;
//     t_texture bg_texture;
//     int pos_x, pos_y;

//     if (!game->portal_gun.img)
//     {
//         printf("Portal gun image is not loaded.\n");
//         return;
//     }

//     portal_gun_texture.img = game->portal_gun.img;
//     portal_gun_texture.addr = (int *)mlx_get_data_addr(portal_gun_texture.img,
//                                                       &portal_gun_texture.pixel_bits,
//                                                       &portal_gun_texture.size_line,
//                                                       &portal_gun_texture.endian);
//     portal_gun_texture.width = game->portal_gun.width;
//     portal_gun_texture.height = game->portal_gun.height;

//     // Crée une texture de fond (background) pour l'overlay
//     bg_texture.img = mlx_new_image(game->mlx, game->win_width, game->win_height);
//     bg_texture.addr = (int *)mlx_get_data_addr(bg_texture.img,
//                                                &bg_texture.pixel_bits,
//                                                &bg_texture.size_line,
//                                                &bg_texture.endian);
//     bg_texture.width = game->win_width;
//     bg_texture.height = game->win_height;

//     // Position de l'image sur l'écran
//     pos_x = (game->win_width - portal_gun_texture.width) / 2;
//     pos_y = game->win_height - portal_gun_texture.height - 10;

//     // Vérifie si l'arme est tirée pour ajuster la position
//     if (game->gun_shot == 1)
//     {
//         pos_y += 10;
//         game->shot_frame++;
//         if (game->shot_frame > 5)
//         {
//             game->gun_shot = 0;
//             game->shot_frame = 0;
//         }
//     }

//     // Superpose l'image du portal gun sur l'image de fond
//     overlay_img(portal_gun_texture, bg_texture, game, pos_x, pos_y);
//     mlx_put_image_to_window(game->mlx, game->win, bg_texture.img, 0, 0);
//     mlx_destroy_image(game->mlx, bg_texture.img);
// }


void	display_portal_gun(t_game *game)
{
	int	x;
	int	y;

	 if (!game->portal_gun.img)
    {
        printf("Portal gun image is not loaded.\n");
        return;
    }
	x = (game->win_width - game->portal_gun.width) / 2;
	y = game->win_height - game->portal_gun.height - 10;
	if (game->gun_shot == 1) // Recul arme
	{
		y += 10;
		game->shot_frame++;
		if (game->shot_frame > 5) // Durée anim'
		{
			game->gun_shot = 0;
			game->shot_frame = 0;
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->portal_gun.img, x, y);
 }

 /*
 La boule doit avoir des coordonnees (pour calculer la distance avec le joueur, ajuster la taille de la boule)
 et une direction
 Boule sur le portal gun et quiva vers le centre de l'ecran.
 Clic gauche => Boule orange apparait / Clic droit => Boule bleue qui apparait
 => Part vers le centre de l'ecran a l'infini tant qu'on ne redemarre pas le programme.
 Prendre en compte la taille de la boule selon la distance  => Later

 */

void create_ball(t_game *game, int button)
{
    t_ball *ball;
    double center_x;
    double center_y;
    double dx;
    double dy;
    double distance;

    ball = NULL;
    if (button == 1)
    {
        ball = &game->ball[0];
        game->ball[1].active = 0;
    }
    else if (button == 3)
    {
        ball = &game->ball[1];
        game->ball[0].active = 0;
    }
    else
    {
        return;
    }

    if (ball && !ball->active)
    {
        // Position de départ
        // ball->x = game->win_width / 2;
        // ball->y = game->win_height - 250;
        // ball->x = (game->win_width - game->portal_gun.width) / 2;
        // ball->y = game->win_height - game->portal_gun.height - 50;
        ball->x = (game->win_width / 2) - (ball->texture.width / 2);
        ball->y = (game->win_height - 180) - (ball->texture.height / 2);
        center_x = game->win_width / 2.0;
        center_y = game->win_height / 2.0;
        dx = center_x - ball->x;
        dy = center_y - ball->y;
        distance = sqrt(dx * dx + dy * dy);
        ball->direction_x = (dx / distance) * 15;
        ball->direction_y = (dy / distance) * 15;
        ball->active = 1;
    }
}


void	load_ball_textures(t_game *game)
{
	game->ball[0].texture.img = mlx_xpm_file_to_image(game->mlx, "src/sprites/sprites/orange_ball.xpm", &game->ball[0].texture.width, &game->ball[0].texture.height);
    if (!game->ball[0].texture.img)
    {
        printf("Failed to load orange ball texture\n");
        free_all2(game);
    }
    game->ball[0].texture.addr = (int *)mlx_get_data_addr(game->ball[0].texture.img, &game->ball[0].texture.pixel_bits, &game->ball[0].texture.size_line, &game->ball[0].texture.endian);

    game->ball[1].texture.img = mlx_xpm_file_to_image(game->mlx, "src/sprites/sprites/blue_ball2.xpm", &game->ball[1].texture.width, &game->ball[1].texture.height);
    if (!game->ball[1].texture.img)
    {
        printf("Failed to load blue ball texture\n");
        free_all2(game);
    }
    game->ball[1].texture.addr = (int *)mlx_get_data_addr(game->ball[1].texture.img, &game->ball[1].texture.pixel_bits, &game->ball[1].texture.size_line, &game->ball[1].texture.endian);
}

void update_balls(t_game *game)
{
	int	i;

	i = 0;
	while (i < 2)
    {
        if (game->ball[i].active)
        {
            // game->ball[i].x += game->ball[i].direction_x;
            // game->ball[i].y += game->ball[i].direction_y;
			move_ball_towards_center(game, &game->ball[i]);
            if (game->ball[i].x < 0 || game->ball[i].x >= game->win_width ||
                game->ball[i].y < 0 || game->ball[i].y >= game->win_height)
            {
                game->ball[i].active = 0;
            }
        }
		i++;
    }
}

void move_ball_towards_center(t_game *game, t_ball *ball)
{
    double center_x;
    double center_y;
    double  dx;
    double  dy;
    double  distance;

    center_x = game->win_width / 2.0;
    center_y = game->win_height / 2.0;
    if (ball->active)
    {
        // Dir. vers le centre
        dx = center_x - (ball->x + ball->texture.width / 2.0);
        dy = center_y - (ball->y + ball->texture.height / 2.0);
        distance = sqrt(dx * dx + dy * dy);

        if (distance > 5.0)
        {
            ball->x += (dx / distance) * 15;
            ball->y += (dy / distance) * 15;
        }
        else // Boule au centre
        {
            ball->x = center_x - (ball->texture.width / 2.0);
            ball->y = center_y - (ball->texture.height / 2.0);
            ball->direction_x = 0;
            ball->direction_y = 0;
        }
    }
}


void draw_ball(t_game *game)
{
    int i;

    i = 0;
    while (i < 2)
    {
        if (game->ball[i].active)
        {
            mlx_put_image_to_window(game->mlx, game->win, game->ball[i].texture.img, game->ball[i].x, game->ball[i].y);
        }
        i++;
    }
}

