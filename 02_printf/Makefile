# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/20 11:26:41 by jaeylee           #+#    #+#              #
#    Updated: 2020/07/27 20:09:48 by jaeylee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	clang
CFLAGS	=	-Wall -Wextra -Werror

HEADERS	=	-I ./includes

NAME	=	libftprintf.a

SRCS	=	./sources/ft_printf.c		\
			./sources/init_flag.c		\
			./sources/flag_process.c	\
			./sources/width_process.c	\
			./sources/precision_process.c	\
			./sources/util.c			\
			./sources/print_s.c			\
			./sources/print_p.c			\
			./sources/print_d.c			\
			./sources/print_u.c			\
			./sources/print_x.c			\
			./sources/print_pc.c			\

OBJS	= $(SRCS:%.c=%.o)

all		:	$(NAME)

$(NAME)	:	$(OBJS)
	ar -rcs $@ $^

%.o		:	%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean	:
	rm -rf $(OBJS)

fclean	:	clean
	rm -rf $(NAME) a.out

re		:	fclean all

gcc		:	all
	gcc $(NAME)
	./a.out

.PHONY :	all clean fclean re gcc
