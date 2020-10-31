/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:38:38 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/09 19:36:13 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	freestorage(char **s)
{
	free(*s);
	*s = NULL;
}

int		appendline(char **storage, char **line)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*storage)[len] != '\n' && (*storage)[len] != '\0')
		len++;
	if ((*storage)[len] == '\n')
	{
		*line = ft_substr(*storage, 0, len);
		tmp = ft_strdup(*storage + len + 1);
		free(*storage);
		*storage = tmp;
		if ((*storage)[0] == '\0')
			freestorage(storage);
	}
	else
	{
		*line = ft_strdup(*storage);
		freestorage(storage);
		return (0);
	}
	return (1);
}

int		output(int fd, char **line, int ret, char **storage)
{
	if (ret < 0)
		return (-1);
	else if (ret == 0 && storage[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (appendline(&storage[fd], line));
}

int		get_next_line(int fd, char **line)
{
	static char	*storage[255];
	int			read_ret;
	char		buf[BUFFER_SIZE + 1];
	char		*tmp;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	while ((read_ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[read_ret] = '\0';
		if (storage[fd] == NULL)
			storage[fd] = ft_strdup(buf);
		else
		{
			tmp = ft_strjoin(storage[fd], buf);
			free(storage[fd]);
			storage[fd] = tmp;
		}
		if (ft_strchr(storage[fd], '\n'))
			break ;
	}
	return (output(fd, line, read_ret, storage));
}
