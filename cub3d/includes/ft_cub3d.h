/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cub3d.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 15:56:59 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 19:53:31 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"
# include "keycode_mac.h"
# include "libft.h"

# define _USE_MATH_DEFINES
# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT		17

# define TEXTURES	10
# define TEX_WIDTH	64
# define TEX_HEIGHT	64
# define NUM_SPRITE 100

# define DIGIT "0123456789"
# define ON		1
# define OFF	0

# define MAP_SPACE		0
# define MAP_WALL		1
# define MAP_SPRITE		2
# define MAP_DOOR_CLOSE	3
# define MAP_DOOR_OPEN	4
# define MAP_TRAP		5

typedef struct	s_img
{
	void		*img;
	int			*data;

	int			size_l;
	int			bpp;
	int			endian;
	int			img_width;
	int			img_height;
}				t_img;

typedef struct	s_point_int
{
	int			x;
	int			y;
}				t_point_i;

typedef struct	s_point_double
{
	double		x;
	double		y;
}				t_point_d;

typedef struct	s_point_float
{
	float		x;
	float		y;
}				t_point_f;

typedef struct	s_draw
{
	int			start;
	int			end;
}				t_draw;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_pair
{
	double		first;
	int			second;
}				t_pair;

typedef struct	s_texture
{
	int			index;
	double		wall_x;
	int			x;
	int			y;
}				t_texture;

typedef struct	s_floor_cast
{
	t_point_f	dir_0;
	t_point_f	dir_1;
	t_point_f	step;
	t_point_f	pos;
	t_point_i	cell;
	t_point_i	tex;
}				t_floor;

typedef struct	s_wall_cast
{
	t_point_d	dir;
	t_point_i	map;
	t_point_d	side;
	t_point_d	delta;
	t_point_i	step;
	int			touch;
	double		w_dist;
	int			line_h;
	t_draw		draw;
	t_texture	tex;
}				t_ray;

typedef struct	s_sprite_cast
{
	int			height;
	int			width;
	int			screen_x;
	t_point_d	pos;
	t_point_d	t;
	t_point_i	draw_start;
	t_point_i	draw_end;
	t_point_i	tex;
}				t_sprite_cast;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	char		dir;

	double		move_speed;
	double		rotate_speed;

	int			life;
}				t_player;

typedef struct	s_move
{
	int			go;
	int			back;
	int			left;
	int			right;
}				t_move;

typedef struct	s_rotate
{
	int			left;
	int			right;
}				t_rotate;

typedef struct	s_rgb
{
	int			r;
	int			g;
	int			b;
	int			color;
}				t_rgb;

typedef struct	s_map
{
	int			screen_width;
	int			screen_height;
	int			w;
	int			h;
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*sprite;
	t_rgb		floor;
	t_rgb		ceiling;
	int			player_num;
	int			sprite_num;
}				t_map;

typedef	struct	s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	p;
	t_move		move;
	t_rotate	rot;
	int			width;
	int			height;
	int			**buf;
	int			texture[TEXTURES][TEX_WIDTH * TEX_HEIGHT];
	int			*skybox;
	int			floor_color;
	int			ceiling_color;
	double		*z_buf;
	int			sprite_order[NUM_SPRITE];
	double		sprite_distance[NUM_SPRITE];
	int			**map;
	t_sprite	sprite[NUM_SPRITE];
	int			horizon;
	int			jump;
	int			open;
	int			damaged;
}				t_game;

int				press_key(int keycode, t_game *game);
int				release_key(int keycode, t_game *game);
int				close_win(t_game *game);

void			raycast(t_game *game);
void			render_wall(t_game *game);
void			touch_wall_pos(t_ray *ray, t_game *game);
void			put_tex_color(t_ray *ray, t_game *game, int i);
void			render_sprite(t_game *game);
void			sort_order(t_pair *orders, int amout);
void			sort_sprites(int *order, double *dist, int amount);

void			draw_texture(t_game *game);

int				col(t_game *game, double x, double y);
int				move_update_go_back(t_game *game);
int				move_update_left_right(t_game *game);
int				rotate_update(t_game *game);
int				jump_update(t_game *game);

void			init_map(t_map *map);
int				sum_atoi(char *s, int *index);
int				get_screen_size(char *s, t_map *map);
int				get_color(char *s, t_rgb *rgb);
int				parse_line(char *s, t_map *map);

int				map_valid_check(char **maze, t_map map);

void			init_direction(t_game *game);
void			player_init(t_game *game);

int				get_next_line(int fd, char **line);

int				export_bmp(t_game *game);
void			map_parse(t_game *game, t_map *map, char *cub_file);

void			game_init(t_game *game, t_map map);
void			init_array(int **arr, int x, int y);
void			exit_error(char *s);
void			free_box(char **box, int len);

void			game_map_init(t_game *game, t_map *map, char **box);
void			player_pos_dir(t_game *game, t_map *map, char **box);

int				is_rgb(int num);
int				is_digit(int num);

void			add_sprite_texture(t_game *game, t_map *map);
int				open_update(t_game *game);
int				trap_update(t_game *game);

int				animated_sprite(t_game *game);

#endif
