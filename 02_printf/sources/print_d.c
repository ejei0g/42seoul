/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 20:35:52 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 19:48:15 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		decimal_length(int num, t_flag *flag)
{
	unsigned int	tmp;
	int				length;

	if (num == 0 && flag->precision != 0)
		return (1);
	length = 0;
	if (num < 0)
		tmp = num * -1;
	else
		tmp = num;
	while (tmp > 0)
	{
		tmp = tmp / 10;
		length++;
	}
	return (length);
}

int		print_decimal(int num, t_flag *flag)
{
	unsigned int	tmp;
	static int		count;

	count = 0;
	if (flag->precision == 0 && num == 0)
		return (0);
	if (num < 0)
		tmp = num * -1;
	else
		tmp = num;
	if (tmp > 9)
		print_decimal(tmp / 10, flag);
	count += write(1, &DECIMAL[tmp % 10], 1);
	return (count);
}

int		print_precision_d(t_flag *flag)
{
	int	tmp;
	int	count;

	count = 0;
	tmp = flag->precision;
	while (tmp > flag->length)
	{
		write(1, "0", 1);
		tmp--;
		count++;
	}
	return (count);
}

int		print_padding_d(t_flag *flag, int num)
{
	int		count;
	char	c;

	c = (flag->zero == ON && flag->precision < 0 && \
			flag->minus == OFF) ? '0' : ' ';
	if (num < 0)
		flag->width--;
	count = 0;
	if (flag->precision < 0 && flag->zero == ON && flag->minus == OFF)
		count += print_minus(num);
	while (flag->width > flag->length && flag->width > flag->precision)
	{
		count += write(1, &c, 1);
		flag->width--;
	}
	if (flag->minus == OFF && (flag->precision >= 0 || flag->zero == OFF))
		count += print_minus(num);
	return (count);
}

int		print_d(t_flag *flag, va_list ap)
{
	int	count;
	int	num;

	num = va_arg(ap, int);
	count = 0;
	flag->length = decimal_length(num, flag);
	if (flag->minus == ON)
	{
		count += print_minus(num);
		count += print_precision_d(flag);
		count += print_decimal(num, flag);
		count += print_padding_d(flag, num);
	}
	else
	{
		count += print_padding_d(flag, num);
		count += print_precision_d(flag);
		count += print_decimal(num, flag);
	}
	return (count);
}
