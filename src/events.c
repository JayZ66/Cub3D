/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:26:16 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/29 18:16:36 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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

// int handle_mouse(int x, int y, t_input *input)
// {
//     if (input->mouse_left_pressed == 1) // Left click
//     {
//         // Logic to detect object selection based on x, y coordinates
//         // If object is selected, set obj->is_selected to true
//     }
//     return 0;
// }

// Maybe put a condition to be sure that we are in the tab. 
// int	manage_keypress(int keycode, t_game *game)
// {
// 	if (keycode >= 0 && keycode < 256)
// 		game->input.keys[keycode] = 1;
// 	printf("Key pressed: %d\n", keycode);
// 	return (0);
// }

int	manage_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		free_all2(game);
	// if (keycode == KEY_UP)
	// 	move_forward(game);
	// else if (keycode == KEY_DOWN)
	// 	move_backward(game);
	else if (keycode == KEY_W)
	{
		printf("LOL\n");
        update_position(game, game->player.dir_x * game->player.speed, game->player.dir_y * game->player.speed);	}
	else if (keycode == KEY_A)
	    update_position(game, game->player.dir_y * game->player.speed, -game->player.dir_x * game->player.speed);
	else if (keycode == KEY_S)
	    update_position(game, -game->player.dir_x * game->player.speed, -game->player.dir_y * game->player.speed);
	else if (keycode == KEY_D)
		update_position(game, -game->player.dir_y * game->player.speed, game->player.dir_x * game->player.speed);
	else if (keycode == KEY_LEFT)
		rotate_player(game, game->player.rot_speed);
	else if (keycode == KEY_RIGHT)
		rotate_player(game, -game->player.rot_speed);
	printf("Key pressed: %d\n", keycode);
	return (0);
}

int	manage_keyrelease(int keycode, t_game *game)
{
	(void)keycode;
	(void)game;
	// if (keycode >= 0 && keycode < 256)
	// 	game->input.keys[keycode] = 0;
	// printf("Key released: %d\n", keycode);
	return (0);
}

int	manage_mouse_movement(int x, t_game *game)
{
	static int	last_x;
	double		angle;
	int			dx;

	last_x = -1;
	if (last_x == -1)
		last_x = x;
	dx = x - last_x; // Diff. de position de la souris.
	last_x = x;
	// Ajuster l'angle de rotation basé sur la différence de position de la souris
	angle = dx * 0.003;
	printf("Before rotation:\n");
    printf("Mouse dx = %d, Angle = %f\n", dx, angle);
    printf("Direction: dir_x = %f, dir_y = %f\n", game->player.dir_x, game->player.dir_y);
    printf("Plane: plane_x = %f, plane_y = %f\n", game->player.plane_x, game->player.plane_y);
	rotate_player(game, angle);
	printf("After rotation:\n");
    printf("Mouse dx = %d, Angle = %f\n", dx, angle);
    printf("Direction: dir_x = %f, dir_y = %f\n", game->player.dir_x, game->player.dir_y);
    printf("Plane: plane_x = %f, plane_y = %f\n", game->player.plane_x, game->player.plane_y);
	return (0);
}

// int	handle_input(t_game *game)
// {
// 	if (game->input.keys[KEY_ESC])
// 		free_all2(game);
// 	// if (game->input.keys[KEY_UP])
// 	// 	move_forward(game);
// 	// else if (game->input.keys[KEY_DOWN])
// 	// 	move_backward(game);
// 	else if (game->input.keys[KEY_W])
// 	{
// 		printf("LOL\n");
// 		update_position(game, 0, -game->player.speed);
// 	}
// 	// else if (game->input.keys[KEY_A])
// 	// 	strafe_left(game);
// 	else if (game->input.keys[KEY_S])
// 		update_position(game, 0, game->player.speed);
// 	// 	move_backward(game);
// 	// else if (game->input.keys[KEY_D])
// 	// 	strafe_right(game);
// 	// else if (game->input.keys[KEY_LEFT])
// 	// 	move_player_direction_to_left(game);
// 	// else if (game->input.keys[KEY_RIGHT])
// 	// 	move_player_direction_to_right(game);
// 	return (0);
// }

// int	game_loop(t_game *game)
// {
// 	handle_input(game);
// 	// render_frame(game);
// 	return (0);
// }

// void	render_frame(t_game *game)
// {

// }
