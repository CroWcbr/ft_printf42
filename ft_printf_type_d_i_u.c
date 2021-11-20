/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_d_i_u.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:18:19 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/14 19:39:56 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_u(unsigned int nbr)
{
	if (nbr >= 10)
		ft_putnbr_u(nbr / 10);
	ft_putchar('0' + (nbr % 10));
}

static int	ft_nbrlen_u(unsigned int nbr)
{
	int	len;

	len = 0;
	while (nbr || len == 0)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

static void	ft_printf_pars_d_i_u_update(t_flags *pars, \
										unsigned long long int nbr)
{
	pars->len = ft_nbrlen_u(nbr);
	if (nbr == 0 && pars->precision_point && pars->precision == 0)
		pars->len = 0;
	pars->pres_len = pars->precision - pars->len;
	if (pars->pres_len < 0)
		pars->pres_len = 0;
	if (pars->len + pars->pres_len + pars->znak > pars->width)
		pars->width = pars->len + pars->pres_len + pars->znak;
	if (pars->flag_minus)
		pars->w_end = pars->width - pars->znak - pars->pres_len - pars->len;
	if (pars->flag_zero && !(pars->flag_minus) && !(pars->precision))
		pars->pres_len = pars->width - pars->znak - pars->len;
	if (!(pars->flag_minus))
	{	
		pars->w_start = pars->width - pars->znak \
						- pars->pres_len - pars->len;
	}
}

static unsigned int	ft_printf_type_d_i_read(t_flags *pars, va_list ap)
{
	unsigned int	utmp;
	int				tmp;

	if (pars->type == 'u')
	{
		utmp = (unsigned int)va_arg(ap, int);
		pars->znak = 0;
		pars->znak_value = '\0';
	}
	else
	{
		tmp = (int)va_arg(ap, int);
		if (tmp < 0)
		{
			pars->znak_value = '-';
			pars->znak = 1;
			utmp = (long int)tmp * -1;
		}
		else
			utmp = tmp;
	}
	return (utmp);
}

int	ft_printf_type_d_i_u(t_flags *pars, va_list ap)
{
	unsigned int	utmp;
	int				i;

	utmp = ft_printf_type_d_i_read(pars, ap);
	i = 0;
	if (utmp == 0 && pars->precision_point && pars->precision == 0)
		i += ft_printf_fill_char_start_end(' ', i, pars->width);
	else
	{	
		ft_printf_pars_d_i_u_update(pars, utmp);
		i += ft_printf_fill_char_start_end(' ', 0, pars->w_start);
		i += ft_printf_fill_char_start_end(pars->znak_value, 0, pars->znak);
		i += ft_printf_fill_char_start_end('0', 0, pars->pres_len);
		if (!(utmp == 0 && pars->precision_point && pars->precision == 0))
			ft_putnbr_u(utmp);
		i += pars->len;
		i += ft_printf_fill_char_start_end(' ', 0, pars->w_end);
	}
	return (i);
}
