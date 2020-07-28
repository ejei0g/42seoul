/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 20:38:21 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 19:49:15 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		x_length(unsigned int num, t_flag *flag)
{
	int	length;

	length = 0;
	if (num == 0 && flag->precision != 0)
		return (1);
	while (num > 0)
	{
		num = num / 16;
		length++;
	}
	return (length);
}

int		print_hex(unsigned int num, t_flag *flag)
{
	static int count;

	count = 0;
	if (flag->precision == 0 && num == 0)
		return (0);
	if (num > 15)
		print_hex(num / 16, flag);
	if (flag->conversion == 'x')
		count += write(1, &HEX_LOWER[num % 16], 1);
	else if (flag->conversion == 'X')
		count += write(1, &HEX_UPPER[num % 16], 1);
	return (count);
}

int		print_pad_x(t_flag *flag)
{
	char	c;
	int		count;

	count = 0;
	c = (flag->zero == ON && flag->precision < 0) ? '0' : ' ';
	while (flag->width > flag->length && flag->width > flag->precision)
	{
		count += write(1, &c, 1);
		flag->width--;
	}
	return (count);
}

int		print_precision_x(t_flag *flag)
{
	int	tmp;
	int	count;

	count = 0;
	tmp = flag->precision;
	while (tmp > flag->length)
	{
		count += write(1, "0", 1);
		tmp--;
	}
	return (count);
}

int		print_x(t_flag *flag, va_list ap)
{
	int				count;
	unsigned int	num;

	num = va_arg(ap, unsigned int);
	count = 0;
	flag->length = x_length(num, flag);
	if (flag->minus == ON)
	{
		count += print_precision_x(flag);
		count += print_hex(num, flag);
		count += print_pad_x(flag);
	}
	else
	{
		count += print_pad_x(flag);
		count += print_precision_x(flag);
		count += print_hex(num, flag);
	}
	return (count);
}
