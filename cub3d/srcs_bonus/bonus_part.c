/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_part.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 17:05:23 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 19:44:09 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	add_sprites_init(t_game *game, t_map *map, int i, int j)
{
	game->sprite[map->sprite_num].x = i + 0.5;
	game->sprite[map->sprite_num].y = j + 0.5;
	if (game->map[i][j] == 2)
		game->sprite[map->sprite_num].texture = 4;
	else
		game->sprite[map->sprite_num].texture = 9;
	map->sprite_num++;
}

void	add_sprite_texture(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			if (game->map[i][j] == 2 || game->map[i][j] == 5)
				add_sprites_init(game, map, i, j);
			j++;
		}
		i++;
	}
}

int		door_col(t_game *g, double move_x, double move_y)
{
	int			i;
	double		len;
	double		rad;
	t_point_d	m;

	len = 1;
	i = 0;
	while (i < 360)
	{
		rad = i * M_PI / 180;
		m.x = g->p.pos_x + move_x + (cos(rad) * len);
		m.y = g->p.pos_y + move_y + (sin(rad) * len);
		if (g->map[(int)m.x][(int)m.y] == 3)
		{
			g->map[(int)m.x][(int)m.y] = 4;
			return (0);
		}
		if (g->map[(int)m.x][(int)m.y] == 4)
		{
			g->map[(int)m.x][(int)m.y] = 3;
			return (0);
		}
		i++;
	}
	return (1);
}

int		open_update(t_game *g)
{
	double	x;
	double	y;

	x = g->p.dir_x * g->p.move_speed;
	y = g->p.dir_y * g->p.move_speed;
	if (g->open == 1)
	{
		if (door_col(g, x, 0))
			g->open = 0;
		if (door_col(g, 0, y))
			g->open = 0;
		return (1);
	}
	return (0);
}

int		trap_update(t_game *g)
{
	if (g->map[(int)g->p.pos_x][(int)g->p.pos_y] == 5 && !g->damaged)
	{
		g->p.life--;
		g->damaged = 1;
		if (g->p.life == 0)
			exit(0);
		return (1);
	}
	else if (g->map[(int)g->p.pos_x][(int)g->p.pos_y] != 5 && g->damaged)
	{
		g->damaged = 0;
		return (1);
	}
	return (0);
}
