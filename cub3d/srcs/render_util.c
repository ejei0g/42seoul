/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:23:25 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/14 23:29:42 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	sort_order(t_pair *orders, int amount)
{
	t_pair	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount - 1)
		{
			if (orders[j].first > orders[j + 1].first)
			{
				tmp.first = orders[j].first;
				tmp.second = orders[j].second;
				orders[j].first = orders[j + 1].first;
				orders[j].second = orders[j + 1].second;
				orders[j + 1].first = tmp.first;
				orders[j + 1].second = tmp.second;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(int *order, double *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	i = 0;
	sprites = (t_pair *)malloc(sizeof(t_pair) * amount);
	while (i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
		i++;
	}
	sort_order(sprites, amount);
	i = 0;
	while (i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
		i++;
	}
	free(sprites);
	sprites = NULL;
}

void	touch_wall_pos(t_ray *ray, t_game *game)
{
	ray->tex.index = game->map[ray->map.x][ray->map.y] - 1;
	if (ray->touch <= 1)
		ray->tex.wall_x = game->p.pos_y + ray->w_dist * ray->dir.y;
	else
		ray->tex.wall_x = game->p.pos_x + ray->w_dist * ray->dir.x;
	ray->tex.wall_x -= floor(ray->tex.wall_x);
	ray->tex.x = (int)(ray->tex.wall_x * (double)TEX_WIDTH);
	if (ray->touch == 1 || ray->touch == 2)
		ray->tex.x = TEX_WIDTH - ray->tex.x - 1;
}

void	put_tex_color(t_ray *r, t_game *g, int i)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	step = 1.0 * TEX_HEIGHT / r->line_h;
	tex_pos = (r->draw.start - g->horizon + r->line_h / 2) * step;
	y = r->draw.start;
	while (y < r->draw.end)
	{
		r->tex.y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = g->texture[r->touch][TEX_HEIGHT * r->tex.y + r->tex.x];
		g->buf[y][i] = color;
		y++;
	}
}
