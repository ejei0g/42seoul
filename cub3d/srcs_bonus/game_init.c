/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 23:25:09 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 23:03:43 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	load_skybox(t_game *game)
{
	t_img	img;
	int		x;
	int		y;
	char	*path;

	path = "textures/skybox.xpm";
	y = 0;
	img.img = mlx_xpm_file_to_image(game->mlx, path,\
			&img.img_width, &img.img_height);
	img.data = (int *)mlx_get_data_addr(img.img, &img.bpp,\
			&img.size_l, &img.endian);
	game->skybox = (int *)malloc(sizeof(int) * img.img_height * img.img_width);
	while (y < img.img_height)
	{
		x = 0;
		while (x < img.img_width)
		{
			game->skybox[img.img_width * y + x] = img.data[img.img_width *\
														y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, img.img);
}

void	load_image(t_game *game, int *texture, char *path)
{
	t_img	img;
	int		x;
	int		y;

	y = 0;
	img.img = mlx_xpm_file_to_image(game->mlx,\
			path, &img.img_width, &img.img_height);
	if (img.img == 0)
		exit_error("texture path error");
	img.data = (int *)mlx_get_data_addr(img.img,\
			&img.bpp, &img.size_l, &img.endian);
	while (y < img.img_height)
	{
		x = 0;
		while (x < img.img_width)
		{
			texture[img.img_width * y + x] = img.data[img.img_width * y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(game->mlx, img.img);
}

void	load_texture(t_game *game, t_map map)
{
	load_image(game, game->texture[0], map.north);
	load_image(game, game->texture[1], map.south);
	load_image(game, game->texture[2], map.west);
	load_image(game, game->texture[3], map.east);
	load_image(game, game->texture[4], map.sprite);
	load_image(game, game->texture[5], "textures/wood.xpm");
	load_image(game, game->texture[6], "textures/fire_4.xpm");
	load_image(game, game->texture[7], "textures/fire_3.xpm");
	load_image(game, game->texture[8], "textures/fire_2.xpm");
	load_image(game, game->texture[9], "textures/fire_1.xpm");
	load_skybox(game);
}

void	init_array(int **arr, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < x)
	{
		j = 0;
		while (j < y)
		{
			arr[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	game_init(t_game *game, t_map map)
{
	int i;

	i = 0;
	game->buf = (int **)malloc(sizeof(int *) * game->height);
	while (i < game->height)
	{
		game->buf[i] = (int *)malloc(sizeof(int) * game->width);
		i++;
	}
	init_array(game->buf, game->height, game->width);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height, "CUBCUB");
	load_texture(game, map);
	game->img.img = mlx_new_image(game->mlx, game->width, game->height);
	game->img.data = (int *)mlx_get_data_addr(game->img.img,\
			&game->img.bpp, &game->img.size_l, &game->img.endian);
}
