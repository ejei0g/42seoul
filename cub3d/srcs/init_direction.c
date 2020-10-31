/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_direction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 17:15:43 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 15:36:17 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	init_direction(t_game *game)
{
	game->p.dir_x = 0.0;
	game->p.dir_y = 0.0;
	game->p.plane_x = 0.0;
	game->p.plane_y = 0.0;
	if (game->p.dir == 'N')
	{
		game->p.dir_x = -1.0;
		game->p.plane_y = 0.66;
	}
	else if (game->p.dir == 'S')
	{
		game->p.dir_x = 1.0;
		game->p.plane_y = -0.66;
	}
	else if (game->p.dir == 'W')
	{
		game->p.dir_y = -1.0;
		game->p.plane_x = -0.66;
	}
	else if (game->p.dir == 'E')
	{
		game->p.dir_y = 1.0;
		game->p.plane_x = 0.66;
	}
}

void	player_init(t_game *game)
{
	init_direction(game);
	game->p.move_speed = 0.25;
	game->p.rotate_speed = 0.15;
	game->move.go = 0;
	game->move.back = 0;
	game->move.left = 0;
	game->move.right = 0;
	game->rot.left = 0;
	game->rot.right = 0;
	game->z_buf = (double *)malloc(sizeof(double) * game->width);
	if (game->z_buf == NULL)
		exit_error("z_buf malloc fail");
	game->horizon = game->height / 2;
	game->jump = 0;
	game->p.life = 5;
}

void	sprites_init(t_game *game, t_map *map, int i, int j)
{
	game->sprite[map->sprite_num].x = i + 0.5;
	game->sprite[map->sprite_num].y = j + 0.5;
	game->sprite[map->sprite_num].texture = 4;
	map->sprite_num++;
}

void	player_pos_dir(t_game *game, t_map *map, char **box)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			if (ft_strchr("012NWSE ", box[i][j]) == 0)
				exit_error("invalid map argument");
			if (ft_strchr("NWSE", box[i][j]))
			{
				game->p.pos_x = i + 0.5;
				game->p.pos_y = j + 0.5;
				game->p.dir = box[i][j];
				map->player_num++;
			}
			if (box[i][j] == '2')
				sprites_init(game, map, i, j);
			j++;
		}
		i++;
	}
}

void	game_map_init(t_game *game, t_map *map, char **box)
{
	int i;
	int j;

	if (!(game->map = (int **)malloc(sizeof(int *) * map->h)))
		exit_error("fail malloc");
	i = 0;
	while (i < map->h)
	{
		if (!(game->map[i] = (int *)malloc(sizeof(int) * map->w)))
			exit_error("fail malloc");
		i++;
	}
	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			game->map[i][j] = (int)box[i][j] - 48;
			if (game->map[i][j] > 64 - 48 && game->map[i][j] < 91 - 48)
				game->map[i][j] = 0;
			j++;
		}
		i++;
	}
}
