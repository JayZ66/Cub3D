/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/25 09:37:20 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

// int	key_press(int keycode, t_input *input)
// {
// 	if (keycode >= 0 && keycode < 256)
// 		input->keys[keycode] = 1;
// 	return (0);
// }

// int	key_release(int keycode, t_input *input)
// {
// 	if (keycode >= 0 && keycode < 256)
// 		input->keys[keycode] = 0;
// }

// int	mouse_press(int button, int x, int y, t_input *input)
// {
// 	if (button == MOUSE_LEFT_CLICK)
// 		input->mouse_left_pressed = 1;
// 	return (0);
// }

// int	mouse_release(int button, int x, int y, t_input *input)
// {
// 	if (button == MOUSE_LEFT_CLICK)
// 		input->mouse_left_pressed = 0;
// 	return (0);
// }

// int	mouse_move(int x, int y, t_input *input)
// {
// 	input->mouse_x = x;
// 	input->mouse_y = y;
// 	return (0);
// }

// Maybe i should separate left/a and right/d
void	manage_keypress(t_game *game, t_input *input)
{
	if (input->keys[KEY_ESC])
		free_all2(game);
	else if (input->keys[KEY_W] || input->keys[KEY_UP])
		move_up();
	else if (input->keys[KEY_S] || input->keys[KEY_DOWN])
		move_down();
	else if (input->keys[KEY_A] || input->keys[KEY_LEFT])
		move_to_left();
	else if (input->keys[KEY_D] || input->keys[KEY_RIGHT])
		move_to_right();
}

void	setup_hooks(t_game *game, t_input *input)
{
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press, input);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_release, input);
	mlx_hook(game->win, KeyPress, KeyPressMask, mouse_press, input);
	mlx_hook(game->win, KeyPress, KeyPressMask, mouse_release, input);
	mlx_hook(game->win, KeyPress, KeyPressMask, mouse_move, input);
}

// mlx_hook(game->win, KeyPress, KeyPressMask, &manage_keypress, game);
// Manage Keypress
void	game_loop(t_game *game, t_input *input)
{
	while (game->running)
	{
		manage_keypress(game, input);
		render_frame(game);
		mlx_hoop_look(game->mlx, &game_loop, game);
	}
}

// Try if game->input.keys[keycode] == KEY_ESC works ??
// int	handle_keypress(int keycode, t_data *data)
// {
//     if (keycode == KEY_ESC)
//     {
//         mlx_destroy_window(data->mlx, data->window);
//         exit(0);
//     }
//     else if (keycode == KEY_W)
//         data->keys.w = 1;
//     else if (keycode == KEY_A)
//         data->keys.a = 1;
//     else if (keycode == KEY_S)
//         data->keys.s = 1;
//     else if (keycode == KEY_D)
//         data->keys.d = 1;
//     else if (keycode == KEY_Q)
//         data->keys.q = 1;
//     else if (keycode == KEY_E)
//         data->keys.e = 1;
//     else if (keycode == KEY_T)
//         data->keys.t = 1;
//     else if (keycode == KEY_Y)
//         data->keys.y = 1;
//     else if (keycode == KEY_G)
//         data->keys.g = 1;
//     else if (keycode == KEY_H)
//         data->keys.h = 1;
//     else if (keycode == KEY_B)
//         data->keys.b = 1;
//     else if (keycode == KEY_N)
//         data->keys.n = 1;
//     return 0;
// }

// int handle_keyrelease(int keycode, t_data *data)
// {
//     if (keycode == KEY_W)
//         data->keys.w = 0;
//     else if (keycode == KEY_A)
//         data->keys.a = 0;
//     else if (keycode == KEY_S)
//         data->keys.s = 0;
//     else if (keycode == KEY_D)
//         data->keys.d = 0;
//     else if (keycode == KEY_Q)
//         data->keys.q = 0;
//     else if (keycode == KEY_E)
//         data->keys.e = 0;
//     else if (keycode == KEY_T)
//         data->keys.t = 0;
//     else if (keycode == KEY_Y)
//         data->keys.y = 0;
//     else if (keycode == KEY_G)
//         data->keys.g = 0;
//     else if (keycode == KEY_H)
//         data->keys.h = 0;
//     else if (keycode == KEY_B)
//         data->keys.b = 0;
//     else if (keycode == KEY_N)
//         data->keys.n = 0;
//     return 0;
// }

// int handle_mouse(int button, int x, int y, t_data *data)
// {
//     if (button == 1) // Left click
//     {
//         // Logic to detect object selection based on x, y coordinates
//         // If object is selected, set obj->is_selected to true
//     }
//     return 0;
// }

/*
JB : SHOULD I MANAGE THE OBJECT POSITION WITH THE EVENTS OR NOT ?
*/