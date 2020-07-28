/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 20:31:55 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 19:53:54 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		u_length(unsigned int num, t_flag *flag)
{
	int	length;

	length = 0;
	if (num == 0 && flag->precision != 0)
		return (1);
	while (num > 0)
	{
		num = num / 10;
		length++;
	}
	return (length);
}

int		print_unsigned(unsigned int num, t_flag *flag)
{
	static int	count;

	count = 0;
	if (flag->precision == 0 && num == 0)
		return (0);
	if (num > 9)
		print_unsigned(num / 10, flag);
	count += write(1, &DECIMAL[num % 10], 1);
	return (count);
}

int		print_pad_u(t_flag *flag)
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

int		print_precision_u(t_flag *flag)
{
	int tmp;
	int count;

	count = 0;
	tmp = flag->precision;
	while (tmp > flag->length)
	{
		count += write(1, "0", 1);
		tmp--;
	}
	return (count);
}

int		print_u(t_flag *flag, va_list ap)
{
	int				count;
	unsigned int	num;

	count = 0;
	num = va_arg(ap, unsigned int);
	flag->length = u_length(num, flag);
	if (flag->minus == ON)
	{
		count += print_precision_u(flag);
		count += print_unsigned(num, flag);
		count += print_pad_u(flag);
	}
	else
	{
		count += print_pad_u(flag);
		count += print_precision_u(flag);
		count += print_unsigned(num, flag);
	}
	return (count);
}
