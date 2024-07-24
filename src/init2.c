
#include "../cub3D.h"

void	init_color(t_color *color)
{
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

void	init_texture(t_texture *texture)
{
	texture->img = NULL;
	texture->addr = NULL;
	texture->pixel_bits = 0;
	texture->size_line = 0;
	texture->endian = 0;
	texture->width = 0;
	texture->height = 0;
}

void	init_input(t_input *input)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		input->keys[i] = 0;
		i++;
	}
	input->last_mouse_x = 0;
	input->last_mouse_y = 0;
	input->last_mouse_x = 0;
	input->last_mouse_y = 0;
	input->mouse_left_pressed = 0;
}
