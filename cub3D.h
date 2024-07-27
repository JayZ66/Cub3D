/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:50:25 by marvin            #+#    #+#             */
/*   Updated: 2024/06/17 12:50:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "Libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "minilibx/mlx.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <errno.h> // perror - strerror
# include <unistd.h> // access - dup2 - execve - fork - pipe - waitpid
# include <sys/wait.h> // Wait
# include <fcntl.h>
# include <math.h>
# include <ctype.h>

# define KEY_ESC 53
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define SZ 32
# define ON_DESTROY 17

// #define KEY_ESC     65307  // Échap (Escape)
// #define KEY_UP      65362  // Flèche haut
// #define KEY_DOWN    65364  // Flèche bas
// #define KEY_W       119    // W
// #define KEY_A       97     // A
// #define KEY_S       115    // S
// #define KEY_D       100    // D
// #define KEY_LEFT    65361  // Flèche gauche
// #define KEY_RIGHT   65363  // Flèche droite
// #define SZ          32     // Espace (Space)

# define MOUSE_LEFT_CLICK 1

typedef enum s_texture_index
{
	NORTH = 0,
	EAST = 1,
	WEST = 2,
	SOUTH = 3
}	t_texture_index;

typedef struct s_input
{
	int	keys[256];
	// int	keys[70000];
	int	mouse_left_pressed;
	int	mouse_x;
	int	mouse_y;
	int	last_mouse_x;
	int	last_mouse_y;
}	t_input;

typedef struct s_texture
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_map		map;
	t_player	player;
	t_texture	textures[4];
	t_color		floor;
	t_color		ceiling;
	t_input		input;
	char		*texture_paths[4];
	int			running;
}	t_game;

// UTILS
int		free_all2(t_game *game);
void	free_everything(t_game *game);
int		ft_isspace(char *line);
int		check_char(char const *set, char c);
int		ft_atoi2(const char *nptr);
int		ft_strncmp_cub(const char *s1, char c, size_t n);
int		only_space(char *line);
int		check_map_line(const char *line);
int		only_space2(char *line);
int		is_description_line(const char *line);
int	error(t_game *game, char *str);

// INITIALIZATION OF STRUCTURES
void	init_cub(t_game *game);
void	init_game(t_game *game);
void	init_texture(t_texture *texture);
void	init_color(t_color *color);
void	init_input(t_input *input);
void	create_window(t_game *game);
void	create_images(t_game *game);
void	read_map(t_game *game, const char *file);
void	malloc_map(t_game *game);
void	fill_map(t_game *game, const char *file);

void	manage_errors(t_game *game, const char *file);
// MAP ERRORS
int		is_map_valid(t_game *game);
int		is_map_empty(t_game *game);
int		is_char_valid(t_game *game);
int		are_walls_valid(t_game *game);
char	**get_map(t_game *game);
int		flood_fill(t_game *game, char **map, int x, int y);
int	is_end_of_map(char *line, int fd);

// FILE ERRORS
int		is_file_valid(const char *file, t_game *game);
int		parse_rgb(char *line, int *r, int *g, int *b);
int		is_rgb_code(t_game *game, char *line);
int		is_path_textures(t_game *game, char *line);
int		are_file_textures_valid(t_game *game);
int		is_file_full(const char *file, t_game *game);
int		are_paths_textures_valid(t_game *game);
int		are_rgb_ids_valid(t_game *game, const char *file);
int	process_map(char *line, int fd, int map_ended);
int	handle_description(char *line);

// EVENTS MANAGEMENT
int		mouse_move(int x, int y, t_input *input);
int		mouse_release(int button, int x, int y, t_input *input);
int		mouse_press(int button, int x, int y, t_input *input);
int		game_loop(t_game *game);
int	handle_input(t_game *game);
int	manage_keyrelease(int keycode, t_game *game);
int	manage_keypress(int keycode, t_game *game);

#endif
