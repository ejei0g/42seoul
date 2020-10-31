/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 22:57:38 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/14 23:46:48 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	exit_error(char *s)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(s, 1);
	ft_putchar_fd('\n', 1);
	exit(1);
}

void	free_box(char **box, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		free(box[i]);
		i++;
	}
	free(box);
}

void	free_buf(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->height)
	{
		free(game->buf[i]);
		i++;
	}
	free(game->buf);
}

int		close_win(t_game *game)
{
	free_buf(game);
	exit(0);
	return (1);
}
