/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:25:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/25 12:48:42 by jeguerin         ###   ########.fr       */
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

int	open_file(const char *file, int fd, t_game *game)
{
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("Could not open the map file\n");
		free_all2(game);
	}
	return (0);
}

int	is_nb_of_rgb_good(int is_ceiling, int is_floor)
{
	if (is_ceiling == 2 || is_floor == 2)
		return (printf("There is a rgb id doublon\n"), 1);
	else if (is_ceiling > 2 || is_floor > 2)
		return (printf("Invalid rgb id\n"), 1);
	return (0);
}

int	ceiling(int is_ceiling, char c)
{
	if (c == 'C')
		is_ceiling++;
	return (is_ceiling);
}

int	floor(int is_floor, char c)
{
	if (c == 'F')
		is_floor++;
	return (is_floor);
}

int	are_rgb_ids_valid(t_game *game, const char *file)
{
	int		fd;
	int		is_floor;
	int		is_ceiling;
	int		i;
	char	*line;

	fd = open_file(file, fd, game);
	is_floor = 0;
	is_ceiling = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL) // Do we need to free a null line ?
			break ;
		i = -1;
		while (line[++i])
		{
			is_ceiling = ceiling(is_ceiling, line[i]);
			is_floor = floor(is_floor, line[i]);
		}
		free(line);
	}
	if (is_nb_of_rgb_good(is_ceiling, is_floor) == 1)
		return (1);
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
// int	is_end_of_map(char *line, int fd)
// {
// 	if (!only_space(line))
// 	{
// 		printf("Map is not the last element in file\n");
// 		free (line);
// 		close(fd);
// 		return (1);
// 	}
// 	return (0);
// }

// int	check_map(char *line, int fd, int map_ended)
// {
// 	if (only_space(line))
// 		map_ended = 1;
// 	else if (!check_map_line(line))
// 	{
// 		printf("Invalid character found in map\n");
// 		free (line);
// 		close (fd);
// 		return (-1);
// 	}
// 	return (map_ended);
// }

int	handle_map_line(char *line, int description)
{
	if (check_map_line(line))
	{
		if (description == 0)
		{
			printf("Map is not at the end of the file\n");
			free(line);
			return (1);
		}
		return (2);
	}
	return (0);
}

// int is_there_something_after_map(const char *file)
// {
//     int fd = open_file(file);

//     int map_started;
//     int map_ended;
//     int description;
//     char *line;

// 	map_started = 0;
//     map_ended = 0;
//     description = 0;
// 	if (fd == -1)
// 	 	return (1);
//     while ((line = get_next_line(fd)) != NULL)
// 	{
//         if (!map_started)
// 		{
//             description = handle_description(line);
//             if (description)
// 				continue ;

//             int map_start_status = handle_map_line(line, description);
//             if (map_start_status == 1)
// 				return (1);
//             if (map_start_status == 2)
// 				map_started = 1;
//         } 
// 		else
// 		{
//             map_ended = process_map(line, fd, map_ended);
//             if (map_ended == 1)
// 				return (1);
//         }
//         free(line);
//     }
//     close(fd);
//     return (0);
// }

int	process_map(char *line, int fd, int map_ended)
{
	if (map_ended)
	{
		if (is_end_of_map(line, fd) == 1)
			return (1);
	}
	else
	{
		map_ended = check_map(line, fd, map_ended);
		if (map_ended == -1)
			return (1);
	}
	return (map_ended);
}

int	handle_description(char *line)
{
	if (is_description_line(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	is_there_something_after_map(const char *file, t_game *game)
{
	int		fd;
	int		map_started;
	int		map_ended;
	int		description;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error(game, "Could not open the map file\n"));
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
			description = handle_description(line);
			if (description)
				continue ;
			else if (check_map_line(line))
			{
				if (description == 0)
					return (printf("Map is not at the end of the file\n"), 1);
				map_started = 1;
			}
		}
		else
		{
			map_ended = process_map(line, fd, map_ended);
			if (map_ended == 1)
				return (1);
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
	if (is_there_something_after_map(file, game) == 1)
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
