/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 17:51:37 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/14 22:53:00 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	init_map(t_map *map)
{
	map->screen_width = 0;
	map->screen_height = 0;
	map->w = 0;
	map->h = 0;
	map->north = 0;
	map->south = 0;
	map->west = 0;
	map->east = 0;
	map->sprite = 0;
	map->floor.r = 0;
	map->floor.g = 0;
	map->floor.b = 0;
	map->floor.color = 0;
	map->ceiling.r = 0;
	map->ceiling.g = 0;
	map->ceiling.b = 0;
	map->ceiling.color = 0;
	map->player_num = 0;
	map->sprite_num = 0;
}

int		sum_atoi(char *s, int *index)
{
	int sum;

	sum = 0;
	while (is_digit(s[*index]))
	{
		sum = sum * 10 + s[*index] - 48;
		*index += 1;
	}
	return (sum);
}

int		get_screen_size(char *s, t_map *map)
{
	int	i;

	i = 0;
	map->screen_width = sum_atoi(s, &i);
	if (s[i] != ' ')
		return (0);
	i++;
	map->screen_height = sum_atoi(s, &i);
	if (map->screen_width == 0 || map->screen_height == 0)
		return (0);
	if (s[i] != 0)
		return (0);
	return (1);
}

int		get_color(char *s, t_rgb *rgb)
{
	int	i;

	i = 0;
	rgb->r = sum_atoi(s, &i);
	if (s[i++] != ',')
		return (0);
	rgb->g = sum_atoi(s, &i);
	if (s[i++] != ',')
		return (0);
	rgb->b = sum_atoi(s, &i);
	if (s[i++] != 0)
		return (0);
	if (!is_rgb(rgb->r) || !is_rgb(rgb->g) || !is_rgb(rgb->b))
		return (0);
	rgb->color = rgb->r * 65536 + rgb->g * 256 + rgb->b;
	return (1);
}

int		parse_line(char *s, t_map *map)
{
	if (*s == 'R' && *(s + 1) == ' ')
		return (get_screen_size(s + 2, map));
	else if (*s == 'N' && *(s + 1) == 'O' && *(s + 2) == ' ')
		map->north = ft_strdup(s + 3);
	else if (*s == 'S' && *(s + 1) == 'O' && *(s + 2) == ' ')
		map->south = ft_strdup(s + 3);
	else if (*s == 'W' && *(s + 1) == 'E' && *(s + 2) == ' ')
		map->west = ft_strdup(s + 3);
	else if (*s == 'E' && *(s + 1) == 'A' && *(s + 2) == ' ')
		map->east = ft_strdup(s + 3);
	else if (*s == 'S' && *(s + 1) == ' ')
		map->sprite = ft_strdup(s + 2);
	else if (*s == 'F' && *(s + 1) == ' ')
		return (get_color(s + 2, &map->floor));
	else if (*s == 'C' && *(s + 1) == ' ')
		return (get_color(s + 2, &map->ceiling));
	else if (*s == '\0')
		return (1);
	else
		return (0);
	return (1);
}
