/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:25:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/23 18:14:36 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_file_extension_valid(const char *file)
{
	int	start_position;
	int	extension;
	int	size;

	size = ft_strlen(file);
	extension = ft_strlen(".cub");
	start_position = size - extension;
	if (start_position < 0 || ft_strcmp(file + start_position, ".cub") != 0)
	{
		printf("Not a .cub file\n");
		return (1);
	}
	return (0);
}

int	is_file_empty(const char *file, t_game *game)
{
	int		fd;
	char	c;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	if (read(fd, &c, 1) == 0)
	{
		printf("File is empty\n");
		close(fd);
		free_all2(game);
	}
	close(fd);
	return (0);
}

/*
Check si une ligne vide puis wall puis wallpuis vide et si apres pas bon !
*/
int	is_file_full(const char *file, t_game *game)
{
	int		fd;
	int		check;
	char	*line;

	check = 0;
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
		if (ft_strncmp_cub(line, '1', ft_strlen(line)) == 0)
			check++;
		if (check == 2 && line != NULL && *line != '\n')
		{
			printf("Map is not the last element in file\n");
			return (1);
		}
	}
	return (0);
}

// Manage if we've a doublon in start position & orientation of the player.
// So : NO/SO/WE/EA
int	are_file_textures_valid(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->texture_paths[i] == NULL)
		{
			printf("Duplicate texture path\n");
			return (1);
		}
		i++;
	}
	return (0);
}

// 	if (access(texture, X_OK) == -1)
// Maybe we must modify our paths to just get the real path (not NO).
int	are_paths_textures_valid(t_game *game)
{
	int		i;
	int		j;
	char	*texture;

	i = 0;
	while (game->texture_paths[i])
	{
		texture = game->texture_paths[i];
		j = 0;
		while (ft_isalpha(texture[j]) == 1 || texture[j] == 32)
			j++;
		texture += j;
		if (access(texture, X_OK) == -1)
		{
			printf("Texture path is wrong\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	are_rgb_ids_valid(t_game *game, const char *file)
{
	int		fd;
	int		is_floor;
	int		is_ceiling;
	int		i;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	is_floor = 0;
	is_ceiling = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{
			free(line);
			break ;
		}
		i = 0;
		while (line[i])
		{
			if (line[i] == 'C')
				is_ceiling++;
			if (line[i] == 'F')
				is_floor++;
			i++;
		}
		free(line);
	}
	printf("Ceiling : %d\n", is_ceiling);
	printf("Floor : %d\n", is_floor);
	if (is_ceiling == 2 || is_floor == 2)
		return (printf("There is a rgb id doublon\n"), 1);
	else if (is_ceiling > 2 || is_floor > 2)
		return (printf("Invalid rgb id\n"), 1);
	return (0);
}

int	is_description_line(const char *line)
{
	return (strncmp(line, "NO ", 3) == 0
		|| strncmp(line, "SO ", 3) == 0
		|| strncmp(line, "WE ", 3) == 0
		|| strncmp(line, "EA ", 3) == 0
		|| strncmp(line, "F ", 2) == 0
		|| strncmp(line, "C ", 2) == 0);
}

int	is_there_something_after_map(const char *file)
{
	int		fd;
	int		map_started;
	int		map_ended;
	int		description;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Could not open the map file\n"), 1);
	map_started = 0;
	map_ended = 0;
	description = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!map_started)
		{
			if (is_description_line(line))
			{
				free(line);
				description = 1;
				continue ;
			}
			else if (check_map_line(line))
			{
				if (description == 0)
					return (printf("Map is not at the end of the file\n"), 1);
				map_started = 1;
			}
		}
		else
		{
			if (map_ended)
			{
				if (!only_space(line))
				{
					printf("Map is not the last element in file\n");
					free (line);
					close(fd);
					return (1);
				}
			}
			else
			{
				if (only_space(line))
					map_ended = 1;
				else if (!check_map_line(line))
				{
					printf("Invalid character found in map\n");
					free (line);
					close (fd);
					return (1);
				}
			}
		}
		free (line);
	}
	close(fd);
	return (0);
}

int	is_file_valid(const char *file, t_game *game)
{
	if (is_file_extension_valid(file) == 1)
		return (1);
	if (is_file_empty(file, game) == 1)
		return (1);
	if (are_file_textures_valid(game) == 1)
		return (1);
	if (are_rgb_ids_valid(game, file) == 1)
		return (1);
	if (is_there_something_after_map(file) == 1)
		return (1);
	if (are_paths_textures_valid(game) == 1)
	{
		return (1);
	}
	return (0);
}
// if (is_there_one_map(file) == 1)
	// 	return (1);
// Texture paths : What's a valid path ???