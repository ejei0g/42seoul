/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <ejei0g@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 18:05:37 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 19:32:44 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		press_key_bonus(int keycode, t_game *game)
{
	if (keycode == KEY_SPACEBAR)
	{
		game->jump = 1;
		game->open = 1;
	}
	else if (keycode == KEY_1)
	{
		game->p.life++;
		if (game->p.life > 5)
			game->p.life = 5;
	}
	else if (keycode == KEY_2)
	{
		game->p.life--;
		if (game->p.life == 0)
			exit(0);
	}
	return (0);
}

int		press_key(int keycode, t_game *game)
{
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->rot.left = 1;
	else if (keycode == KEY_W || keycode == KEY_UP)
		game->move.go = 1;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		game->rot.right = 1;
	else if (keycode == KEY_A)
		game->move.left = 1;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		game->move.back = 1;
	else if (keycode == KEY_D)
		game->move.right = 1;
	else if (keycode == KEY_ESCAPE)
		exit(0);
	else if (keycode == KEY_R)
		game->horizon = game->height / 1.7;
	else if (keycode == KEY_F)
		game->horizon = game->height / 3;
	press_key_bonus(keycode, game);
	return (0);
}

int		release_key(int keycode, t_game *game)
{
	if (keycode == KEY_Q || keycode == KEY_LEFT)
		game->rot.left = 0;
	else if (keycode == KEY_W || keycode == KEY_UP)
		game->move.go = 0;
	else if (keycode == KEY_E || keycode == KEY_RIGHT)
		game->rot.right = 0;
	else if (keycode == KEY_A)
		game->move.left = 0;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		game->move.back = 0;
	else if (keycode == KEY_D)
		game->move.right = 0;
	else if (keycode == KEY_SPACEBAR)
		;
	else if (keycode == KEY_R)
		game->horizon = game->height / 2;
	else if (keycode == KEY_F)
		game->horizon = game->height / 2;
	return (0);
}

int		col(t_game *g, double move_x, double move_y)
{
	int		i;
	double	len;
	double	rad;
	double	x;
	double	y;

	len = 0.1;
	i = 0;
	while (i < 360)
	{
		rad = i * M_PI / 180;
		x = g->p.pos_x + move_x + (cos(rad) * len);
		y = g->p.pos_y + move_y + (sin(rad) * len);
		if (g->map[(int)x][(int)y] > 0 && g->map[(int)x][(int)y] < 4)
			return (0);
		i++;
	}
	return (1);
}
