/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:26:44 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 18:26:52 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		meet_(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (TRUE);
		s++;
	}
	return (FALSE);
}

int		is_digit(char c)
{
	if ('0' <= c && c <= '9')
		return (TRUE);
	else
		return (FALSE);
}

int		print_minus(int num)
{
	if (num < 0)
	{
		write(1, "-", 1);
		return (1);
	}
	else
		return (0);
}
