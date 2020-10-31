/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <ejei0g@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 18:11:36 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 00:51:10 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	draw_hud(t_game *game)
{
	int	i;
	int	hud_len;
	int	void_len;
	int	tmp;

	hud_len = 20;
	void_len = 6;
	tmp = game->width / 2 - game->height / 2;
	i = game->height / 2 - hud_len;
	while (i < game->height / 2 + hud_len)
	{
		if (i > game->height / 2 + void_len || i < game->height / 2 - void_len)
			game->buf[i][game->width / 2] = 0x00FFFF;
		if (i + tmp > game->width / 2 + void_len ||\
				i + tmp < game->width / 2 - void_len)
			game->buf[game->height / 2][i + tmp] = 0x00FFFF;
		i++;
	}
}

void	draw_lifebar(t_game *game)
{
	int	i;
	int	j;
	int	len;

	len = game->p.life * 100;
	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < 30)
		{
			if (i % 100 < 10)
				;
			else
				game->buf[j][i] = 0xff0000;
			j++;
		}
		i++;
	}
}

void	draw_texture(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	draw_hud(game);
	draw_lifebar(game);
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			game->img.data[y * game->width + x] = game->buf[y][x];
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}
