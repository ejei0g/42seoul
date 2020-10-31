/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:38:52 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/14 23:25:56 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "libft.h"
# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 32

int		appendline(char **storage, char **line);
int		output(int fd, char **line, int ret, char **storage);
int		get_next_line(int fd, char **line);

#endif
