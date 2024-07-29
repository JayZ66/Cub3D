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
int	manage_keypress(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->input.keys[keycode] = 1;
	printf("Key pressed: %d\n", keycode);
	return (0);
}

int	manage_keyrelease(int keycode, t_game *game)
{
	if (keycode >= 0 && keycode < 256)
		game->input.keys[keycode] = 0;
	printf("Key released: %d\n", keycode);
	return (0);
}

int	handle_input(t_game *game)
{
	if (game->input.keys[KEY_ESC])
		free_all2(game);
	// if (game->input.keys[KEY_UP])
	// 	move_forward(game);
	// else if (game->input.keys[KEY_DOWN])
	// 	move_backward(game);
	else if (game->input.keys[KEY_W])
	{
		printf("LOL\n");
		update_position(game, 0, -game->player.speed);
	}
	// else if (game->input.keys[KEY_A])
	// 	strafe_left(game);
	else if (game->input.keys[KEY_S])
		update_position(game, 0, game->player.speed);
	// 	move_backward(game);
	// else if (game->input.keys[KEY_D])
	// 	strafe_right(game);
	// else if (game->input.keys[KEY_LEFT])
	// 	move_player_direction_to_left(game);
	// else if (game->input.keys[KEY_RIGHT])
	// 	move_player_direction_to_right(game);
	return (0);
}

// 	int	handle_input(t_game *game)
// {
// 	if (game->input.keys[KEY_ESC])
// 		free_all2(game);
// 	if (game->input.keys[KEY_UP])
// 		// move_forward(game);
// 	else if (game->input.keys[KEY_DOWN])
// 		// move_backward(game);
// 	else if (game->input.keys[KEY_W])
// 		// move_forward(game);
// 	else if (game->input.keys[KEY_A])
// 		// strafe_left(game); // Déplacement à gauche
// 	else if (game->input.keys[KEY_S])
// 		// move_backward(game);
// 	else if (game->input.keys[KEY_D])
// 		// strafe_right(game); // Déplacement à droite
// 	else if (game->input.keys[KEY_LEFT])
// 		// move_player_direction_to_left(game);
// 	else if (game->input.keys[KEY_RIGHT])
// 		// move_player_direction_to_right(game);
// 	return (0);
// }

int	game_loop(t_game *game)
{
	handle_input(game);
	// render_frame(game);
	return (0);
}

// void	render_frame(t_game *game)
// {

// }
