/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:36:47 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/14 22:49:58 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	calc_sprite_distance(t_game *g)
{
	int	i;

	i = 0;
	while (i < NUM_SPRITE)
	{
		g->sprite_order[i] = i;
		g->sprite_distance[i] = ((g->p.pos_x - g->sprite[i].x) * (g->p.pos_x\
					- g->sprite[i].x) + (g->p.pos_y - g->sprite[i].y) *\
				(g->p.pos_y - g->sprite[i].y));
		i++;
	}
}

void	calc_sprite_vector(t_game *g, t_sprite_cast *s, int i)
{
	double	vec;

	s->pos.x = g->sprite[g->sprite_order[i]].x - g->p.pos_x;
	s->pos.y = g->sprite[g->sprite_order[i]].y - g->p.pos_y;
	vec = 1.0 / (g->p.plane_x * g->p.dir_y - g->p.dir_x * g->p.plane_y);
	s->t.x = vec * (g->p.dir_y * s->pos.x - g->p.dir_x * s->pos.y);
	s->t.y = vec * (-g->p.plane_y * s->pos.x + g->p.plane_x * s->pos.y);
}

void	calc_sprite_texture(t_game *g, t_sprite_cast *s, int i)
{
	int	x;
	int	y;
	int	d;
	int	color;
	int	index;

	x = s->draw_start.x;
	while (x < s->draw_end.x)
	{
		s->tex.x = (int)(256 * (x - (-s->width / 2 + s->screen_x)) *\
				TEX_WIDTH / s->width) / 256;
		y = s->draw_start.y;
		while (y < s->draw_end.y && s->t.y > 0 && x > 0 \
				&& x < g->width && s->t.y < g->z_buf[x])
		{
			d = (y - (g->horizon - g->height / 2)) * 2 - g->height + s->height;
			s->tex.y = ((d * TEX_HEIGHT * 128) / s->height) / 256;
			index = TEX_WIDTH * s->tex.y + s->tex.x;
			color = g->texture[g->sprite[g->sprite_order[i]].texture][index];
			if ((color & 0x00FFFFFF) != 0)
				g->buf[y][x] = color;
			y++;
		}
		x++;
	}
}

void	calc_sprite_draw_point(t_game *game, t_sprite_cast *s, int i)
{
	s->screen_x = (int)((game->width / 2) * (1 + s->t.x / s->t.y));
	s->height = abs((int)((game->height) / (s->t.y)));
	s->width = abs((int)(game->height / (s->t.y)));
	s->draw_start.y = -s->height / 2 + game->horizon;
	if (s->draw_start.y < 0)
		s->draw_start.y = 0;
	s->draw_end.y = s->height / 2 + game->horizon;
	if (s->draw_end.y >= game->height)
		s->draw_end.y = game->height - 1;
	s->draw_start.x = -s->width / 2 + s->screen_x;
	if (s->draw_start.x < 0)
		s->draw_start.x = 0;
	s->draw_end.x = s->width / 2 + s->screen_x;
	if (s->draw_end.x >= game->width)
		s->draw_end.x = game->width - 1;
	calc_sprite_texture(game, s, i);
}

void	render_sprite(t_game *game)
{
	t_sprite_cast	s;
	int				i;

	calc_sprite_distance(game);
	sort_sprites(game->sprite_order, game->sprite_distance, NUM_SPRITE);
	i = 0;
	while (i < NUM_SPRITE)
	{
		calc_sprite_vector(game, &s, i);
		calc_sprite_draw_point(game, &s, i);
		i++;
	}
}
