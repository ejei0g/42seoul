/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 22:25:52 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 17:14:22 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

void	link_map_game(t_game *game, t_map *map)
{
	game->width = map->screen_width;
	game->height = map->screen_height;
	game->floor_color = map->floor.color;
	game->ceiling_color = map->ceiling.color;
}

void	map_size_check(t_map *map, t_list *copy)
{
	t_list *tmp;

	map->h = ft_lstsize(copy);
	map->w = 0;
	tmp = copy;
	while (copy)
	{
		if (map->w < (int)ft_strlen(copy->content))
			map->w = (int)ft_strlen(copy->content);
		copy = copy->next;
	}
	copy = tmp;
}

t_list	*map_get_line(t_map *map, char *cub_file)
{
	int		fd;
	char	*line;
	t_list	*copy;

	line = 0;
	if ((fd = open(cub_file, O_RDONLY)) == -1)
		exit_error("incorrect .cub file");
	while (get_next_line(fd, &line) > 0)
	{
		if (!parse_line(line, map))
			exit_error("parsing - invalid info(element)");
		if (line[0] == '\0')
			break ;
		free(line);
	}
	free(line);
	copy = 0;
	while (get_next_line(fd, &line) > 0)
	{
		ft_lstadd_back(&copy, ft_lstnew(ft_strdup(line)));
		free(line);
	}
	free(line);
	close(fd);
	return (copy);
}

char	**make_box(t_map *map, t_list *copy)
{
	t_list	*tmp;
	char	**box;
	int		i;
	int		j;
	char	*copyline;

	tmp = copy;
	box = (char **)malloc(sizeof(char *) * (map->h + 1));
	i = 0;
	while (copy)
	{
		j = 0;
		box[i] = (char *)malloc(sizeof(char) * (map->w + 1));
		copyline = (char *)copy->content;
		while (j < (int)ft_strlen(copy->content))
			box[i][j++] = *copyline++;
		while (j < map->w)
			box[i][j++] = ' ';
		box[i][map->w] = '\0';
		i++;
		copy = copy->next;
	}
	box[i] = (char *)'\0';
	copy = tmp;
	return (box);
}

void	map_parse(t_game *game, t_map *map, char *cub_file)
{
	char	**box;
	t_list	*copy;

	init_map(map);
	copy = map_get_line(map, cub_file);
	link_map_game(game, map);
	map_size_check(map, copy);
	box = make_box(map, copy);
	player_pos_dir(game, map, box);
	ft_lstclear(&copy, free);
	if (map->player_num != 1)
		exit_error("character over");
	if (map_valid_check(box, *map) == 0)
		exit_error("map valid error");
	game_map_init(game, map, box);
	add_sprite_texture(game, map);
	free_box(box, map->h);
}
