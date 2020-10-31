/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 00:08:40 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 01:12:33 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	render_skybox(t_game *game, int *color, int x, int y)
{
	double	width;
	int		height;
	double	double_width;

	double_width = game->width;
	width = x / (double_width / 580);
	height = y / (game->height / 326);
	*color = game->skybox[580 * height + (int)width];
}

void	calc_floor_casting(t_floor *f, t_game *game, int y)
{
	int		p;
	float	z;
	float	r_dis;

	f->dir_0.x = game->p.dir_x - game->p.plane_x;
	f->dir_0.y = game->p.dir_y - game->p.plane_y;
	f->dir_1.x = game->p.dir_x + game->p.plane_x;
	f->dir_1.y = game->p.dir_y + game->p.plane_y;
	p = y - game->horizon;
	z = 0.5 * game->height;
	r_dis = z / p;
	f->step.x = r_dis * (f->dir_1.x - f->dir_0.x) / game->width;
	f->step.y = r_dis * (f->dir_1.y - f->dir_0.y) / game->width;
	f->pos.x = game->p.pos_x + r_dis * f->dir_0.x;
	f->pos.y = game->p.pos_y + r_dis * f->dir_0.y;
}

void	calc_floor_texture(t_floor *f)
{
	f->cell.x = (int)(f->pos.x);
	f->cell.y = (int)(f->pos.y);
	f->tex.x = (int)(64 * (f->pos.x - (float)f->cell.x)) & (TEX_WIDTH - 1);
	f->tex.y = (int)(64 * (f->pos.y - (float)f->cell.y)) & (TEX_HEIGHT - 1);
	f->pos.x += f->step.x;
	f->pos.y += f->step.y;
}

void	render_floor(t_game *game)
{
	t_floor	f;
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < game->height)
	{
		calc_floor_casting(&f, game, y);
		x = 0;
		while (x < game->width)
		{
			calc_floor_texture(&f);
			if (y > game->horizon)
				color = game->texture[5][TEX_WIDTH * f.tex.y - f.tex.x];
			else
				render_skybox(game, &color, x, y);
			game->buf[y][x] = color;
			x++;
		}
		y++;
	}
}

void	raycast(t_game *game)
{
	render_floor(game);
	render_wall(game);
	render_sprite(game);
}
