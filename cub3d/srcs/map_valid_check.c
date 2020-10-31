/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:15:49 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/14 22:31:55 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	valid_left_side(char **map, t_map m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m.h)
	{
		j = 0;
		while (j < m.w && map[i][j] != '1')
		{
			if (map[i][j] != ' ')
				return (0);
			j++;
		}
		while (j < m.w - 1)
		{
			if ((map[i][j] == '0' || map[i][j] == '2') && map[i][j + 1] == ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_right_side(char **map, t_map m)
{
	int i;
	int j;

	i = 0;
	while (i < m.h)
	{
		j = 0;
		while (j < m.w && map[i][m.w - j - 1] != '1')
		{
			if (map[i][m.w - j - 1] != ' ')
				return (0);
			j++;
		}
		while (j < m.w - 1)
		{
			if ((map[i][m.w - j - 1] == '0' || \
					map[i][m.w - j - 1] == '2') && map[i][m.w - j - 2] == ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_top_side(char **map, t_map m)
{
	int i;
	int j;

	i = 0;
	while (i < m.w)
	{
		j = 0;
		while (j < m.h && map[j][i] != '1')
		{
			if (map[j][i] != ' ')
				return (0);
			j++;
		}
		while (j < m.h - 1)
		{
			if ((map[j][i] == '0' || map[j][i] == '2') && map[j + 1][i] == ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	valid_bottom_side(char **map, t_map m)
{
	int i;
	int j;

	i = 0;
	while (i < m.w)
	{
		j = 0;
		while (j < m.h && map[m.h - j - 1][i] != '1')
		{
			if (map[m.h - j - 1][i] != ' ')
				return (0);
			j++;
		}
		while (j < m.h - 1)
		{
			if ((map[m.h - j - 1][i] == '0' || \
					map[m.h - j - 1][i] == '2') && map[m.h - j - 2][i] == ' ')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	map_valid_check(char **maze, t_map map)
{
	if (!valid_left_side(maze, map))
		return (0);
	if (!valid_right_side(maze, map))
		return (0);
	if (!valid_top_side(maze, map))
		return (0);
	if (!valid_bottom_side(maze, map))
		return (0);
	return (1);
}
