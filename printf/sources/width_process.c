/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:27:21 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 17:29:34 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

unsigned int	put_ap(va_list ap, t_flag *flag)
{
	unsigned int	tmp;
	int				copy;

	copy = va_arg(ap, int);
	if (copy < 0)
	{
		flag->minus = ON;
		tmp = copy * (-1);
	}
	else
		tmp = copy;
	return (tmp);
}

void			width_process(t_flag *flag, const char *input, va_list ap)
{
	if (input[flag->current] == '*')
	{
		flag->width = put_ap(ap, flag);
		flag->current++;
	}
	else if (is_digit(input[flag->current]))
	{
		while (is_digit(input[flag->current]))
		{
			flag->width = flag->width * 10;
			flag->width = flag->width + input[flag->current] - 48;
			flag->current++;
		}
	}
	return ;
}
