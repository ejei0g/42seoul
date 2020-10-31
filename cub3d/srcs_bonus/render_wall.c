/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:19:50 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 17:16:14 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void		calc_raycasting(t_ray *ray, t_game *game, int i)
{
	double	camera_x;

	camera_x = 2 * i / (double)game->width - 1;
	ray->dir.x = game->p.dir_x + game->p.plane_x * camera_x;
	ray->dir.y = game->p.dir_y + game->p.plane_y * camera_x;
	ray->map.x = (int)game->p.pos_x;
	ray->map.y = (int)game->p.pos_y;
	ray->delta.x = fabs(1 / ray->dir.x);
	ray->delta.y = fabs(1 / ray->dir.y);
}

void		check_quadrant(t_ray *ray, t_game *game)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side.x = (game->p.pos_x - ray->map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side.x = (ray->map.x + 1.0 - game->p.pos_x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side.y = (game->p.pos_y - ray->map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side.y = (ray->map.y + 1.0 - game->p.pos_y) * ray->delta.y;
	}
}

void		execute_dda(t_ray *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->map.x += ray->step.x;
			ray->touch = (ray->step.x == -1) ? 0 : 1;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->map.y += ray->step.y;
			ray->touch = (ray->step.y == -1) ? 2 : 3;
		}
		if (game->map[ray->map.x][ray->map.y] == 1)
			hit = 1;
		if (game->map[ray->map.x][ray->map.y] == 3)
			hit = 1;
	}
}

void		calc_perp_dist(t_ray *r, t_game *g, int i)
{
	if (r->touch <= 1)
		r->w_dist = (r->map.x - g->p.pos_x + (1 - r->step.x) / 2) / r->dir.x;
	else
		r->w_dist = (r->map.y - g->p.pos_y + (1 - r->step.y) / 2) / r->dir.y;
	g->z_buf[i] = r->w_dist;
	r->line_h = (int)(g->height / r->w_dist);
	r->draw.start = -r->line_h / 2 + g->horizon;
	if (r->draw.start < 0)
		r->draw.start = 0;
	r->draw.end = r->line_h / 2 + g->horizon;
	if (r->draw.end >= g->height)
		r->draw.end = g->height - 1;
}

void		render_wall(t_game *game)
{
	t_ray	r;
	int		i;

	i = 0;
	while (i < game->width)
	{
		calc_raycasting(&r, game, i);
		check_quadrant(&r, game);
		execute_dda(&r, game);
		calc_perp_dist(&r, game, i);
		touch_wall_pos(&r, game);
		put_tex_color(&r, game, i);
		i++;
	}
}
