# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/09 18:45:38 by jaeylee           #+#    #+#              #
#    Updated: 2020/10/15 19:52:45 by jaeylee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3d
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
FRAMEWORK	=	-framework OpenGL -framework AppKit
INCS		=	-I./includes -I./mlx -I./libft
LIBS		=	-lmlx -L./mlx -lft -L./libft
LIBFT		=	./libft

SRCS		=	./srcs/main.c				\
				./srcs/deal_key.c			\
	 			./srcs/render.c				\
				./srcs/raycasting.c			\
				./srcs/get_next_line.c		\
				./srcs/parsing.c			\
				./srcs/map_valid_check.c	\
				./srcs/init_direction.c		\
				./srcs/export_bmp.c			\
				./srcs/exit_program.c		\
				./srcs/map_parse.c			\
				./srcs/game_init.c			\
				./srcs/update_state.c		\
				./srcs/render_sprite.c		\
				./srcs/render_wall.c		\
				./srcs/render_util.c		\
				./srcs/utils.c				\

SRCS_BONUS	=	./srcs_bonus/main.c				\
				./srcs_bonus/deal_key.c			\
	 			./srcs_bonus/render.c			\
				./srcs_bonus/raycasting.c		\
				./srcs_bonus/get_next_line.c	\
				./srcs_bonus/parsing.c			\
				./srcs_bonus/map_valid_check.c	\
				./srcs_bonus/init_direction.c	\
				./srcs_bonus/export_bmp.c		\
				./srcs_bonus/exit_program.c		\
				./srcs_bonus/map_parse.c		\
				./srcs_bonus/game_init.c		\
				./srcs_bonus/update_state.c		\
				./srcs_bonus/render_sprite.c	\
				./srcs_bonus/render_wall.c		\
				./srcs_bonus/render_util.c		\
				./srcs_bonus/utils.c			\
				./srcs_bonus/bonus_part.c		\
				./srcs_bonus/animate.c			\

OBJS		=	$(SRCS:%.c=%.o)
OBJS_BONUS	=	$(SRCS_BONUS:%.c=%.o)

%.o:		%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCS)

all:		$(NAME)
#	./cub3d

$(NAME):	$(OBJS)
	$(MAKE) -C $(LIBFT) bonus
	$(CC) $(CFLAGS) $(FRAMEWORK) $(OBJS) $(LIBS) $(INCS) -o $@

clean:
	$(MAKE) -C $(LIBFT) clean
	rm -f $(OBJS) $(OBJS_BONUS)

fclean:		clean
	$(MAKE) -C $(LIBFT) fclean
	rm -f $(NAME)

re:			fclean all

bonus:		$(OBJS_BONUS)
	$(MAKE) -C $(LIBFT) bonus
	$(CC) $(CFLAGS) $(FRAMEWORK) $(OBJS_BONUS) $(LIBS) $(INCS) -o $(NAME)

.PHONY	:	all clean fclean re bonus
