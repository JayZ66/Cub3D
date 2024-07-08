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
# include "minilibx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

typedef enum e_texture_index {
    NORTH = 0,
    SOUTH = 1,
    EAST = 2,
    WEST = 3
} e_texture_index;

typedef struct s_texture {
    void    *img;
    int     *addr;
    int     pixel_bits;
    int     size_line;
    int     endian;
    int     width;
    int     height;
} t_texture;

typedef struct s_color {
    int r;
    int g;
    int b;
} t_color;

typedef struct s_map {
    char **map;
    int width;
    int height;
} t_map;

typedef struct s_player {
    double x;
    double y;
    double dir_x;
    double dir_y;
    double plane_x;
    double plane_y;
} t_player;

typedef struct s_game {
    void        *mlx;
    void        *win;
    int         win_height;
    int         win_width;
    t_map       map;
    t_player    player;
    t_texture   textures[4];
    t_color     floor;
    t_color     ceiling;
    char        *texture_paths[4];
} t_game;

// UTILS

// INITIALIZATION OF STRUCTURES

#endif
