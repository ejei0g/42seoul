/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 22:23:46 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/14 22:35:25 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void	write_bmp_header(t_game *game, int fd, int size)
{
	unsigned char	header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	set_int_in_char(header + 2, size);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	set_int_in_char(header + 18, game->width);
	set_int_in_char(header + 22, game->height);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
}

void	write_bmp_data(t_game *game, int fd)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					pad;

	i = game->height;
	pad = (4 - (game->width * 3) % 4) % 4;
	while (i >= 0)
	{
		j = 0;
		while (j < game->width)
		{
			write(fd, &(game->buf[i][j]), 3);
			if (pad > 0)
				write(fd, &zero, pad);
			j++;
		}
		i--;
	}
}

int		export_bmp(t_game *game)
{
	int	fd;
	int	size;

	size = 54 + 3 * game->width * game->height;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC \
					| O_APPEND, 00755)) < 0)
		return (-1);
	write_bmp_header(game, fd, size);
	write_bmp_data(game, fd);
	return (1);
}
