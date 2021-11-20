/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_p_x_X.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 18:46:43 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/15 16:25:33 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_fill_str_start_end(char *s, int flag, int end)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	if (flag)
	{
		ft_putstr(s);
		i += len;
		i += ft_printf_fill_char_start_end(' ', i, end);
	}
	else
	{
		i += ft_printf_fill_char_start_end(' ', i, end - len);
		ft_putstr(s);
		i += len;
	}
	return (i);
}

static void	ft_printf_pars_x_p_update(t_flags *pars, \
										unsigned long int nbr, int base)
{
	pars->len = ft_printf_nbrlen_ull_hex(nbr, base);
	pars->pres_len = pars->precision - pars->len;
	if (pars->pres_len < 0)
		pars->pres_len = 0;
	if (pars->len + pars->pres_len + pars->flag_hash * 2 > pars->width)
		pars->width = pars->len + pars->pres_len + pars->flag_hash * 2;
	if (pars->flag_minus)
		pars->w_end = pars->width - pars->flag_hash * 2 - \
						pars->pres_len - pars->len;
	if (pars->flag_zero && !(pars->flag_minus) && !(pars->precision))
		pars->pres_len = pars->width - pars->flag_hash * 2 - pars->len;
	if (!(pars->flag_minus))
		pars->w_start = pars->width - pars->flag_hash * 2 - \
						pars->pres_len - pars->len;
}

int	ft_printf_type_x(t_flags *pars, va_list ap)
{
	unsigned long long int	tmp;
	int						i;

	tmp = (unsigned int)va_arg(ap, int);
	if (tmp == 0)
		pars->flag_hash = 0;
	i = 0;
	if (tmp == 0 && pars->precision_point && pars->precision == 0)
		i += ft_printf_fill_char_start_end(' ', i, pars->width);
	else
	{
		ft_printf_pars_x_p_update(pars, tmp, 16);
		i += ft_printf_fill_char_start_end(' ', 0, pars->w_start);
		i += ft_printf_fill_char_start_end('0', 0, pars->flag_hash);
		i += ft_printf_fill_char_start_end(pars->type, 0, pars->flag_hash);
		i += ft_printf_fill_char_start_end('0', 0, pars->pres_len);
		if (pars->type == 'x')
			ft_printf_putnbr_ull_hex(tmp, "0123456789abcdef", 16);
		else
			ft_printf_putnbr_ull_hex(tmp, "0123456789ABCDEF", 16);
		i += pars->len;
		i += ft_printf_fill_char_start_end(' ', 0, pars->w_end);
	}
	return (i);
}

int	ft_printf_type_p(t_flags *pars, va_list ap)
{
	unsigned long long int	tmp;
	int						i;

	tmp = (unsigned long long int)va_arg(ap, void *);
	i = 0;
	if (tmp == 0)
		i += ft_printf_fill_str_start_end("0x0", \
			pars->flag_minus, pars->width);
	else
	{
		pars->flag_hash = 1;
		ft_printf_pars_x_p_update(pars, tmp, 16);
		i += ft_printf_fill_char_start_end(' ', 0, pars->w_start);
		i += ft_printf_fill_char_start_end('0', 0, pars->flag_hash);
		i += ft_printf_fill_char_start_end('x', 0, pars->flag_hash);
		i += ft_printf_fill_char_start_end('0', 0, pars->pres_len);
		ft_printf_putnbr_ull_hex(tmp, "0123456789abcdef", 16);
		i += pars->len;
		i += ft_printf_fill_char_start_end(' ', 0, pars->w_end);
	}
	return (i);
}
