
#include "../cub3D.h"

void    render_mini_map(t_game *game, t_texture *frame)
{
    t_texture mini_map;

    (void)frame;
    mini_map.width = M_SIZE * T_SIZE;
    mini_map.height = M_SIZE * T_SIZE;
    mini_map.img = mlx_new_image(game->mlx, mini_map.width, mini_map.height);
    mini_map.addr = (int *)mlx_get_data_addr(mini_map.img, &mini_map.pixel_bits, &mini_map.size_line, &mini_map.endian);

    draw_mini_map(game, &mini_map);
    draw_player(game, &mini_map);

    mlx_put_image_to_window(game->mlx, game->win, mini_map.img, 10, 10); // Positionne la mini-map
    mlx_destroy_image(game->mlx, mini_map.img);
}

void    draw_mini_map(t_game *game, t_texture *mini_map)
{
    int x;
    int y;
    int map_x;
    int map_y;

    y = 0;
    while (y < M_SIZE)
    {
        x = 0;
        while (x < M_SIZE)
        {
            map_x = game->player.x - (M_SIZE / 2) + x;
            map_y = game->player.y - (M_SIZE / 2) + y;
            if (map_x >= 0 && map_x < game->map.width && map_y >= 0 && map_y < game->map.height)
            {
                if (game->map.map[map_y][map_x] == '1')
                    draw(mini_map, x, y, 0xFFFFFF);
                else if (game->map.map[map_y][map_x] == '0')
                    draw(mini_map, x, y, 0x888888);
                else
                    draw(mini_map, x, y, 0x000000);
            }
            else
                draw(mini_map, x, y, 0x555555); // Outside of map
            x++;
        }
        y++;
    }
}

void    draw(t_texture *img, int x, int y, int color)
{
    int i;
    int j;
    int pixel_x;
    int pixel_y;

    i = 0;
    while (i < T_SIZE)
    {
        j = 0;
        while (j < T_SIZE)
        {
            pixel_x = x * T_SIZE + i;
            pixel_y = y * T_SIZE + j;
            if (pixel_x < img->width && pixel_y < img->height)
                my_mlx_pixel_put(img, pixel_x, pixel_y, color);
            j++;
        }
        i++;
    }
}

void    draw_player(t_game *game, t_texture *mini_map)
{
    int player_x;
    int player_y;
    int pixel_x;
    int pixel_y;
    int i;
    int j;

    player_x = M_SIZE / 2 * T_SIZE;
    player_y = M_SIZE / 2 * T_SIZE;
    i = 0;
    while (i < 4) // Parcourir 4 pixels pour former le square (height)
    {
        j = 0;
        while (j < 4) // (width)
        {
            pixel_x = player_x + i;
            pixel_y = player_y + j;
            my_mlx_pixel_put(mini_map, pixel_x, pixel_y, 0xFF0000); // Red for player
            j++;
        }
        i++;
    }
    draw_view_direction(game, mini_map);
}

void    draw_view_direction(t_game *game, t_texture *mini_map)
{
    int player_x;
    int player_y;
    int x;
    int y;
    int i;

    player_x = M_SIZE / 2 * T_SIZE;
    player_y = M_SIZE / 2 * T_SIZE;
    i = 0;
    while (i < 10)
    {
        x = player_x + i * game->player.dir_x;
        y = player_y + i * game->player.dir_y;
        my_mlx_pixel_put(mini_map, x, y, 0xFF0000); // Red for direction
        i++;
    }
}

void my_mlx_pixel_put(t_texture *img, int x, int y, int color)
{
    char *dst;

    dst = (char *)img->addr + (y * img->size_line + x * (img->pixel_bits / 8));
    *(unsigned int *)dst = color;
}


/*
FAIRE UN DEUXIEME JEU A PART : 
- Prendre map parsé
- Prendre position joueur
- Quand portail passé on réaffiche tout (refaire fonction rendering)
=> Réappeler la fonction qui affiche la map.
*/