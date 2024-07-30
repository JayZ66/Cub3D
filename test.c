
#include "../cub3D.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map.cub>", NULL);
	init_data(&data);
	data.map.map_path = ft_strdup(argv[1]);
	init_map(&data);
	// init_textures(&data);
	// init_colors(&data);
	mlx_hook(data.win, 2, 1L<<0, handle_keypress, &data);
	mlx_hook(data.win, 3, 1L<<1, handle_keyrelease, &data);
	mlx_hook(data.win, 17, 0, cross_quit, &data);
	mlx_loop_hook(data.mlx, render_frame, &data);
	mlx_do_key_autorepeaton(data.mlx);
	mlx_loop(data.mlx);
	// cleanup(&data);
	return (0);
}

void init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		error_exit("Failed to initialize MLX", data);
	data->win = mlx_new_window(data->mlx, 800, 600, "Cub3D");
	if (!data->win)
		error_exit("Failed to create window", data);
	data->player.dir_x = -1;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0.66;
	data->player.speed = 0.2; // Vitesse du joueur en pixels
	data->player.pov_speed = 3.0;
}

int handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		quit(data);
	else if (keycode == KEY_W)
		update_player_position_2(data, 0);
	else if (keycode == KEY_A)
		update_player_position_2(data, 1);
	else if (keycode == KEY_S)
		update_player_position_2(data, 2);
	else if (keycode == KEY_D)
		update_player_position_2(data, 3);
	else if (keycode == KEY_R_ARROW)
		update_player_dir(data, -1);
	else if (keycode == KEY_L_ARROW)
		update_player_dir(data, 1);
	return (0);
}

int handle_keyrelease(int keycode, t_data *data)
{
	// Pour l'instant, ne fait rien
	return (0);
}

void update_player_position_2(t_data *data, int dir)
{
	double	d_x;
	double	d_y;
	double	d_dir;

	d_dir = dir * 90;
	d_dir += data->player.deg_dir;
	if (d_dir > 360)
		d_dir -= 360;
	d_x = data->player.speed * sin(degrad(d_dir));
	d_y = data->player.speed * cos(degrad(d_dir));
	update_player_position(data, d_x, d_y);
}

void update_player_position(t_data *data, double delta_x, double delta_y)
{
	double	new_x;
	double	new_y;

	new_x = data->player.x + delta_x;
	new_y = data->player.y + delta_y;
	if (!is_collision(data, new_x, data->player.y))
		data->player.x = new_x;
	if (!is_collision(data, data->player.x, new_y))
		data->player.y = new_y;
}

int is_collision(t_data *data, double x, double y)
{
	int map_x;
	int map_y;

	map_x = (int)(x);
	map_y = (int)(y);

	if (map_x < 0 || map_x >= data->map.map_dim.x || map_y < 0 || map_y >= data->map.map_dim.y)
		return 1; // Treat out-of-bounds as a collision
	if (data->map.map[map_y][map_x] == '1' || data->map.map[map_y][map_x] == ' ')
		return 1;
	return (0);
}