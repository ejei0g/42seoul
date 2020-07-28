/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 14:04:00 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 17:58:27 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	flag_process(t_flag *flag, const char *input)
{
	while (meet_(FLAG, input[flag->current]))
	{
		if (input[flag->current] == '-')
			flag->minus = ON;
		else if (input[flag->current] == '0')
			flag->zero = ON;
		flag->current++;
	}
}
