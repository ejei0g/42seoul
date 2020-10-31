/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 18:20:29 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 19:52:21 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int	main_loop(t_game *game)
{
	static int	update = 1;

	update += move_update_go_back(game);
	update += move_update_left_right(game);
	update += rotate_update(game);
	update += jump_update(game);
	update += open_update(game);
	update += trap_update(game);
	update += animated_sprite(game);
	raycast(game);
	draw_texture(game);
	init_array(game->buf, game->height, game->width);
	if (update)
		mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	update = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;
	int		option;

	option = (argc >= 2 && (ft_strncmp(argv[1], "--save", 6) == 0)) ? 1 : 0;
	if (argc < option + 2)
		exit_error("invalid argument");
	map_parse(&game, &map, argv[option + 1]);
	game_init(&game, map);
	player_init(&game);
	if (option == 1)
	{
		raycast(&game);
		draw_texture(&game);
		if (export_bmp(&game) == -1)
			exit_error("export file error");
		exit(0);
	}
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &press_key, &game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, &release_key, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &close_win, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
