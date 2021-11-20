/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:04:23 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/15 16:23:57 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_ft_printf_flags
{
	int		flag_minus;
	int		flag_zero;
	int		precision_point;
	int		precision;
	int		width;
	int		flag_hash;
	int		flag_space;
	int		flag_plus;
	char	type;
	int		znak;	
	char	znak_value;
	int		w_start;
	int		pres_len;
	int		len;	
	int		w_end;
}t_flags;

typedef struct s_ft_printf_set
{
	t_flags		*pars;
	const char	*format;
	va_list		ap;
	int			len;
}t_ft_printf_set;

int		ft_printf(const char *format, ...);

int		ft_printf_pars(t_flags *pars, const char *format);

int		ft_printf_type_c(t_flags *pars, va_list ap);
int		ft_printf_type_s(t_flags *pars, va_list ap);
int		ft_printf_type_p(t_flags *pars, va_list ap);
int		ft_printf_type_x(t_flags *pars, va_list ap);
int		ft_printf_type_d_i_u(t_flags *pars, va_list ap);
int		ft_printf_type_percent(t_flags *pars, va_list ap);

int		ft_printf_fill_char_start_end(char c, int start, int end);
void	ft_printf_putnbr_ull_hex(unsigned long long int n, \
									char *base, int base_len);
int		ft_printf_nbrlen_ull_hex(unsigned long long int nbr, int base_len);

void	ft_putchar(char c);
void	ft_putstr(char *s);

#endif
