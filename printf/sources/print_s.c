/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 19:58:49 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 17:27:36 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		print_pad_s(t_flag *flag)
{
	char	c;
	int		count;
	int		len;

	len = flag->length;
	c = (flag->zero == ON && flag->precision < 0 \
			&& flag->minus == OFF) ? '0' : ' ';
	count = 0;
	if (flag->precision < flag->length && flag->precision >= 0)
		len = flag->precision;
	while (flag->width > len)
	{
		count += write(1, &c, 1);
		flag->width--;
	}
	return (count);
}

int		print_str(t_flag *flag, char *s)
{
	int	count;
	int len;

	count = 0;
	len = flag->length;
	if (flag->precision < flag->length && flag->precision >= 0)
		len = flag->precision;
	while (len > count)
	{
		write(1, &s[count], 1);
		count++;
	}
	return (count);
}

int		print_s(t_flag *flag, va_list ap)
{
	int		count;
	char	*s;

	count = 0;
	s = va_arg(ap, char *);
	if (s == NULL)
		s = "(null)";
	flag->length = ft_strlen(s);
	if (flag->minus == ON)
	{
		count += print_str(flag, s);
		count += print_pad_s(flag);
	}
	else
	{
		count += print_pad_s(flag);
		count += print_str(flag, s);
	}
	return (count);
}
