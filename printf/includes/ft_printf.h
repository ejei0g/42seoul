/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 11:32:47 by jaeylee           #+#    #+#             */
/*   Updated: 2020/07/27 20:08:19 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

# define CONVERSION "cspdiuxX%"
# define FLAG "-0"
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER "0123456789ABCDEF"
# define DECIMAL "0123456789"

# define ON 1
# define OFF 0
# define TRUE 1
# define FALSE 0
# define ERROR -1

typedef struct	s_flag
{
	int		minus;
	int		zero;
	int		width;
	int		precision;
	int		length;
	int		current;
	char	conversion;
}				t_flag;

int				ft_printf(const char *input, ...);

void			init_flag(t_flag *new_flag);
void			flag_process(t_flag *flag, const char *input);
void			width_process(t_flag *flag, const char *input, va_list ap);
void			precision_process(t_flag *flag, const char *input, va_list ap);

int				print_s(t_flag *flag, va_list ap);
int				print_p(t_flag *flag, va_list ap);
int				print_d(t_flag *flag, va_list ap);
int				print_u(t_flag *flag, va_list ap);
int				print_x(t_flag *flag, va_list ap);
int				print_pc(t_flag *flag, va_list ap);

int				ft_strlen(char *s);
int				meet_(const char *s, char c);
int				is_digit(char c);
int				print_minus(int num);

#endif
