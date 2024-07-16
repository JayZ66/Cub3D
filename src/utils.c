/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:24:13 by jeguerin          #+#    #+#             */
/*   Updated: 2024/07/10 19:41:50 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	check_char(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_isspace(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] <= 9 || line[i] >= 13 || line[i] != 32)
			return (1);
		i++;
	}
	return (0);
}

int	free_all2(t_game *game)
{
	int	i;

	printf("OK free \n");
	if (game->map.map)
	{
		i = 0;
		while (i < game->map.height)
		{
			// printf("Line %s\n", game->map.map[i]);
			if (game->map.map[i])
				free(game->map.map[i]);
			i++;
		}
		free(game->map.map);
	}
	i = 0;
	while (i < 4)
	{
		if (game->texture_paths[i])
			free(game->texture_paths[i]);
		i++;
	}
	if (game->win != NULL)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(EXIT_FAILURE);
}

int	ft_atoi2(const char *nptr)
{
	int		i;
	int		sign;
	int		result;
	int		check;

	i = 0;
	sign = 1;
	result = 0;
	check = -1;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == 43 || nptr[i] == 45)
	{
		if (nptr[i + 1] == 45 || nptr[i + 1] == 43)
			return (0);
		if (nptr[i] == 45)
			sign = -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = result * 10 + (nptr[i] - '0');
		check = 0;
		i++;
	}
	if (check == -1)
		return (-1);
	return (result * sign);
}

int	ft_strncmp_cub(const char *s1, char c, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == 32)
		i++;
	while ((unsigned char)s1[i] && ((unsigned char)s1[i]
			== (unsigned char)c) && (i < n - 1))
	{
		printf("Char : %c\n", s1[i]);
		i++;
	}
	if (i == n - 1)
	{
		printf("OK\n");
		return (0);
	}
	else
		return (1);
}
