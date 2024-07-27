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
	// if (game->input.keys[KEY_ESC]) // CREATE ERROR !!
	// 	free_all2(game);
	if (game->input.keys[KEY_UP])
	{
		printf("OK\n");
		// move_forward(game);
	}
	else if (game->input.keys[KEY_DOWN])
		printf("Ok1\n");
		// move_backward(game);
	else if (game->input.keys[KEY_W])
		printf("Ok2\n");
		// move_forward(game);
	else if (game->input.keys[KEY_A])
		printf("Ok3\n");
		// strafe_left(game); // Déplacement à gauche
	else if (game->input.keys[KEY_S])
		printf("Ok4\n");
		// move_backward(game);
	else if (game->input.keys[KEY_D])
		printf("Ok5\n");
		// strafe_right(game); // Déplacement à droite
	else if (game->input.keys[KEY_LEFT])
		printf("Ok6\n");
		// move_player_direction_to_left(game);
	else if (game->input.keys[KEY_RIGHT])
		printf("Ok7\n");
		// move_player_direction_to_right(game);
	return (0);
}

int	game_loop(t_game *game)
{
	handle_input(game);
	// render_frame(game);
	return (0);
}

// void	render_frame(t_game *game)
// {

// }
