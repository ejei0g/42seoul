/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 20:39:59 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 17:29:02 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	print_width_cp(t_flag *flag)
{
	char	c;
	int		count;

	count = 0;
	c = (flag->zero == ON && flag->precision < 0 \
			&& flag->minus == OFF) ? '0' : ' ';
	if (flag->minus == OFF && flag->zero == ON)
		c = '0';
	while (flag->width > flag->length)
	{
		count += write(1, &c, 1);
		flag->width--;
	}
	return (count);
}

int	print_pc(t_flag *flag, va_list ap)
{
	int		count;
	char	c;

	count = 0;
	flag->length = 1;
	if (flag->conversion == 'c')
		c = va_arg(ap, int);
	else
		c = '%';
	if (flag->minus == ON)
	{
		count += write(1, &c, 1);
		count += print_width_cp(flag);
	}
	else
	{
		count += print_width_cp(flag);
		count += write(1, &c, 1);
	}
	return (count);
}
