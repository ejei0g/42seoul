/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 17:53:46 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 20:08:42 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		p_length(long num, t_flag *flag)
{
	int	len;

	len = 0;
	if (num == 0 && flag->precision != 0)
		return (1);
	while (num > 0)
	{
		num = num / 16;
		len++;
	}
	return (len);
}

int		print_pointer(long num, t_flag *flag)
{
	static int count;

	count = 0;
	if (flag->precision == 0 && num == 0)
		return (0);
	if (num > 15)
		print_pointer(num / 16, flag);
	count += write(1, &HEX_LOWER[num % 16], 1);
	return (count);
}

int		print_pad_p(t_flag *flag)
{
	char	c;
	int		count;
	int		len;

	len = flag->length;
	count = 0;
	c = (flag->zero == ON && flag->precision < 0) ? '0' : ' ';
	if (flag->precision > flag->length)
		len = flag->precision;
	while (flag->width > len + 2)
	{
		count += write(1, &c, 1);
		flag->width--;
	}
	return (count);
}

int		print_precision_p(t_flag *flag)
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

int		print_p(t_flag *flag, va_list ap)
{
	int		count;
	long	p;

	p = va_arg(ap, long);
	count = 0;
	flag->length = p_length(p, flag);
	if (flag->minus == ON)
	{
		count += write(1, "0x", 2);
		count += print_precision_p(flag);
		count += print_pointer(p, flag);
		count += print_pad_p(flag);
	}
	else
	{
		count += print_pad_p(flag);
		count += write(1, "0x", 2);
		count += print_precision_p(flag);
		count += print_pointer(p, flag);
	}
	return (count);
}
