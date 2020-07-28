/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:53:57 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 15:17:41 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	precision_process(t_flag *flag, const char *input, va_list ap)
{
	if (input[flag->current] == '.')
		flag->precision = 0;
	if (input[flag->current] == '.' && input[flag->current + 1] == '*')
	{
		flag->precision = va_arg(ap, int);
		flag->current += 2;
	}
	else if (input[flag->current] == '.' && is_digit(input[flag->current + 1]))
	{
		flag->current++;
		flag->precision = 0;
		while (is_digit(input[flag->current]))
		{
			flag->precision *= 10;
			flag->precision = flag->precision + input[flag->current] - 48;
			flag->current++;
		}
	}
	return ;
}
