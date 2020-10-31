/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:05:18 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 17:00:34 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		jump_update(t_game *game)
{
	static double	num = 1.7;
	int				update;

	update = 0;
	if (game->jump)
	{
		game->horizon = game->height / num;
		num = num + 0.1;
		if (num > 2)
			num = 2;
		if (num == 2.0)
		{
			update = 0;
			game->jump = 0;
			game->horizon = game->height / 2;
			num = 1.7;
			return (update);
		}
		update = 1;
	}
	return (update);
}

int		rotate_update(t_game *g)
{
	double	old_dir_x;
	double	old_plane_x;
	double	ro;

	old_dir_x = g->p.dir_x;
	old_plane_x = g->p.plane_x;
	ro = g->p.rotate_speed;
	if (g->rot.left == 1)
	{
		g->p.dir_x = g->p.dir_x * cos(ro) - g->p.dir_y * sin(ro);
		g->p.dir_y = old_dir_x * sin(ro) + g->p.dir_y * cos(ro);
		g->p.plane_x = g->p.plane_x * cos(ro) - g->p.plane_y * sin(ro);
		g->p.plane_y = old_plane_x * sin(ro) + g->p.plane_y * cos(ro);
		return (1);
	}
	else if (g->rot.right == 1)
	{
		g->p.dir_x = g->p.dir_x * cos(-ro) - g->p.dir_y * sin(-ro);
		g->p.dir_y = old_dir_x * sin(-ro) + g->p.dir_y * cos(-ro);
		g->p.plane_x = g->p.plane_x * cos(-ro) - g->p.plane_y * sin(-ro);
		g->p.plane_y = old_plane_x * sin(-ro) + g->p.plane_y * cos(-ro);
		return (1);
	}
	return (0);
}

int		chk_wall(t_game *g, double x, double y)
{
	double px;
	double py;

	px = g->p.pos_x + x;
	py = g->p.pos_y + y;
	if (g->map[(int)px][(int)py] == 0)
		return (1);
	if (g->map[(int)px][(int)py] == 4)
		return (1);
	if (g->map[(int)px][(int)py] == 5)
		return (1);
	return (0);
}

int		move_update_left_right(t_game *g)
{
	double	x;
	double	y;

	x = g->p.dir_x * g->p.move_speed;
	y = g->p.dir_y * g->p.move_speed;
	if (g->move.left == 1)
	{
		if (chk_wall(g, -y, 0) && col(g, -y, 0))
			g->p.pos_x -= y;
		if (chk_wall(g, 0, x) && col(g, 0, x))
			g->p.pos_y += x;
		return (1);
	}
	else if (g->move.right == 1)
	{
		if (chk_wall(g, y, 0) && col(g, y, 0))
			g->p.pos_x += y;
		if (chk_wall(g, 0, -x) && col(g, 0, -x))
			g->p.pos_y -= x;
		return (1);
	}
	return (0);
}

int		move_update_go_back(t_game *g)
{
	double	x;
	double	y;

	x = g->p.dir_x * g->p.move_speed;
	y = g->p.dir_y * g->p.move_speed;
	if (g->move.go == 1)
	{
		if (chk_wall(g, x, 0) && col(g, x, 0))
			g->p.pos_x += x;
		if (chk_wall(g, 0, y) && col(g, 0, y))
			g->p.pos_y += y;
		return (1);
	}
	else if (g->move.back == 1)
	{
		if (chk_wall(g, -x, 0) && col(g, -x, 0))
			g->p.pos_x -= x;
		if (chk_wall(g, 0, -y) && col(g, 0, -y))
			g->p.pos_y -= y;
		return (1);
	}
	return (0);
}
