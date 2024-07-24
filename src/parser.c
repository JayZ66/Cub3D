/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:56:31 by marvin            #+#    #+#             */
/*   Updated: 2024/07/08 13:56:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

/* MAP ERRORS
	5. Map shape errors
		a. Check si la map est carrée (par contre check JB's tickets car
		la map n'est pas toujours carrée mais il faut qd même le check).
*/

int	check_map_line(const char *line)
{
	int	has_valid_char;

	has_valid_char = 0;
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == 'N' || *line == 'S'
			|| *line == 'W' || *line == 'E')
			has_valid_char = 1;
		else if (*line != ' ' && *line != '\t' && *line != '\n' && *line != '\r'
			&& is_description_line(line) == 0)
			return (0);
		line++;
	}
	return (has_valid_char);
}

void	manage_width(t_game *game, char *line)
{
	int	line_length;

	line_length = 0;
	line_length = ft_strlen(line);
	if (line[line_length - 1] == '\n')
		line_length--;
	if (line_length > game->map.width)
		game->map.width = line_length;
	game->map.height++;
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
}

// NEED TO CHECK : Ligne vide entre textures, rgb et map !
void	fill_map(t_game *game, const char *file)
{
	int		i;
	int		fd;
	int		textures;
	int		rgb;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	textures = 0;
	rgb = 0;
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	memset(game->map.map, 0, sizeof(char *) * (game->map.height));
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (textures != 4 && is_path_textures(game, line) == 0)
			textures += 1;
		else if (rgb != 2 && is_rgb_code(game, line) == 0)
			rgb += 1;
		else if (check_map_line(line) == 1)
		{
			if (i >= game->map.height)
			{
				printf("Error: map height exceeded allocated space\n");
				free(line);
				break ;
			}
			game->map.map[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	if (rgb != 2 || textures != 4)
	{
		printf("Map description is either wrong or incomplete\n");
		free_all2(game);
	}
	close(fd);
}

/*
if (*line == ',')
=> Should we manage the error ? Yes !
*/
int	parse_rgb(char *line, int *r, int *g, int *b)
{
	*r = ft_atoi2(line);
	if (*r == -1)
		return (printf("Red color code is missing\n"), 1);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	else
		return (1);
	*g = ft_atoi2(line);
	if (*g == -1)
		return (printf("Green color code is missing\n"), 1);
	while (ft_isdigit(*line))
		line++;
	if (*line == ',')
		line++;
	else
		return (1);
	*b = ft_atoi2(line);
	if (*b == -1)
		return (printf("Blue color code is missing\n"), 1);
	while (ft_isdigit(*line))
		line++;
	if (*line != '\0' && *line != '\n')
		return (1);
	if ((*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		&& ft_isspace(line) != 1)
		return (1);
	return (0);
}

int	is_rgb_code(t_game *game, char *line)
{
	int		r;
	int		g;
	int		b;
	char	*rgb_line;

	if ((line[0] == 'C' || line[0] == 'F') && line[1] == ' ')
	{
		rgb_line = line + 2;
		if (parse_rgb(rgb_line, &r, &g, &b) == 1)
		{
			if (line[0] == 'C')
				printf("Invalid ceiling RGB color\n");
			else
				printf("Invalid floor RGB color\n");
			free_all2(game);
		}
		if (line[0] == 'F')
		{
			game->floor.r = r;
			game->floor.g = g;
			game->floor.b = b;
		}
		else if (line[0] == 'C')
		{
			game->ceiling.r = r;
			game->ceiling.g = g;
			game->ceiling.b = b;
		}
		return (0);
	}
	else if (check_char(line, 32) != 1 && check_char(line, '\n') != 1)
	{
		printf("Invalid id for RGB color\n");
		free(line);
		free_all2(game);
	}
	return (1);
}

int	is_path_textures(t_game *game, char *line)
{
	if (game->texture_paths[NORTH] == 0 && ft_strncmp(line, "NO", 2) == 0
		&& line[2] == ' ')
		game->texture_paths[NORTH] = ft_strdup(line + 3);
	else if (game->texture_paths[SOUTH] == 0 && ft_strncmp(line, "SO", 2) == 0
		&& line[2] == ' ')
		game->texture_paths[SOUTH] = ft_strdup(line + 3);
	else if (game->texture_paths[WEST] == 0 && ft_strncmp(line, "WE", 2) == 0
		&& line[2] == ' ')
		game->texture_paths[WEST] = ft_strdup(line + 3);
	else if (game->texture_paths[EAST] == 0 && ft_strncmp(line, "EA", 2) == 0
		&& line[2] == ' ')
		game->texture_paths[EAST] = ft_strdup(line + 3);
	else
		return (1);
	return (0);
}
// printf("Textures : %s\n", game->texture_paths[NORTH]);
// printf("Textures : %s\n", game->texture_paths[SOUTH]);
// printf("Textures : %s\n", game->texture_paths[WEST]);
// printf("Textures : %s\n", game->texture_paths[EAST]);

void	manage_errors(t_game *game, const char *file)
{
	if (is_file_valid(file, game) == 1)
		free_all2(game);
	if (is_map_valid(game) == 1)
		free_all2(game);
}
