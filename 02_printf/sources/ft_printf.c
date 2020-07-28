/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:32:19 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 17:53:38 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		print_process(t_flag *flag, va_list ap)
{
	int	print_count;

	print_count = 0;
	if (flag->conversion == 'c' || flag->conversion == '%')
		print_count += print_pc(flag, ap);
	else if (flag->conversion == 's')
		print_count += print_s(flag, ap);
	else if (flag->conversion == 'p')
		print_count += print_p(flag, ap);
	else if (flag->conversion == 'd' || flag->conversion == 'i')
		print_count += print_d(flag, ap);
	else if (flag->conversion == 'u')
		print_count += print_u(flag, ap);
	else if (flag->conversion == 'x' || flag->conversion == 'X')
		print_count += print_x(flag, ap);
	return (print_count);
}

void	parse_process(const char *input, t_flag *flag, va_list ap)
{
	flag->current++;
	flag_process(flag, input);
	width_process(flag, input, ap);
	precision_process(flag, input, ap);
	while (!meet_(CONVERSION, input[flag->current]))
		flag->current++;
	flag->conversion = input[flag->current++];
}

int		ft_printf(const char *input, ...)
{
	va_list	ap;
	int		print_count;
	t_flag	data;

	data.current = 0;
	print_count = 0;
	va_start(ap, input);
	while (input[data.current] != '\0')
	{
		if (input[data.current] == '%')
		{
			init_flag(&data);
			parse_process(input, &data, ap);
			print_count += print_process(&data, ap);
		}
		else
			print_count += write(1, &input[data.current++], 1);
	}
	va_end(ap);
	return (print_count);
}
