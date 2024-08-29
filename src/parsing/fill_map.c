/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:33:07 by jeguerin          #+#    #+#             */
/*   Updated: 2024/08/29 17:46:11 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

void	loop_to_fill_map(t_game *game, int fd, int *textures, int *rgb)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (check_textures_and_rgb(game, line, textures, rgb) == 1)
		{
			free(line);
			continue ;
		}
		else if (check_map_line(line) == 1)
		{
			am_i_going_to_far(game, line, i);
			game->map.map[i++] = ft_strdup(line);
		}
		free(line);
	}
}

void	fill_map(t_game *game, const char *file)
{
	int		fd;
	int		textures;
	int		rgb;

	textures = 0;
	rgb = 0;
	fd = 1;
	fd = open_file(file, fd, game);
	memset(game->texture_paths, 0, sizeof(game->texture_paths));
	memset(game->map.map, 0, sizeof(char *) * (game->map.height));
	loop_to_fill_map(game, fd, &textures, &rgb);
	check_nb_of_rgb_textures(rgb, textures, game, fd);
	close(fd);
}

/* MAP ERRORS
	5. Map shape errors
		a. Check si la map est carrée (par contre check JB's tickets car
		la map n'est pas toujours carrée mais il faut qd même le check).
*/
int	check_map_line(char *line)
{
	int	has_valid_char;

	has_valid_char = 0;
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == 'N' || *line == 'S'
			|| *line == 'W' || *line == 'E' || *line == 'D')
			has_valid_char = 1;
		else if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r'
			&& is_description_line(line) == 0)
			return (0);
		line++;
	}
	return (has_valid_char);
}

// printf("height : %d\n", game->map.height);
// printf("width : %d\n", game->map.width);
void	read_map(t_game *game, const char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (check_map_line(line) == 1)
			manage_width(game, line);
		free(line);
	}
	close(fd);
}

// printf("Height : %d\n", game->map.height);
void	malloc_map(t_game *game)
{
	game->map.map = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (game->map.map == NULL)
	{
		printf("Could not allocate memory\n");
		return ;
	}
	game->map.map[game->map.height] = NULL;
	printf("height : %d\n", game->map.height);
	printf("width : %d\n", game->map.width);
}
