/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:22:22 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 17:26:56 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	init_flag(t_flag *new_flag)
{
	new_flag->width = 0;
	new_flag->precision = -1;
	new_flag->length = 0;
	new_flag->minus = OFF;
	new_flag->zero = OFF;
	new_flag->conversion = 0;
	return ;
}
