/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/23 18:12:54 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	key_press(int keycode, t_input *input)
{
	if (keycode >= 0 && keycode < 256)
		input->keys[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_input *input)
{
	if (keycode >= 0 && keycode < 256)
		input->keys[keycode] = 0;
}

int	mouse_press(int button, int x, int y, t_input *input)
{
	if (button == MOUSE_LEFT_CLICK)
		input->mouse_left_pressed = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, t_input *input)
{
	if (button == MOUSE_LEFT_CLICK)
		input->mouse_left_pressed = 0;
	return (0);
}

int	mouse_move(int x, int y, t_input *input)
{
	input->mouse_x = x;
	input->mouse_y = y;
	return (0);
}

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

// mlx_hook(game->win, KeyPress, KeyPressMask, &manage_keypress, game); // Manage Keypress