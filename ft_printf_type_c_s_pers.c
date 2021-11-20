/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_type_c_s_pers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:07:29 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/14 19:54:34 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_type_c(t_flags *pars, va_list ap)
{
	unsigned char	tmp;
	int				i;

	tmp = (unsigned char)va_arg(ap, int);
	i = 0;
	if (pars->flag_minus)
	{
		ft_putchar(tmp);
		i++;
		i += ft_printf_fill_char_start_end(' ', i, pars->width);
	}
	else
	{
		i += ft_printf_fill_char_start_end(' ', i, pars->width - 1);
		ft_putchar(tmp);
		i++;
	}
	return (i);
}

static void	ft_printf_pars_s_update(t_flags *pars, \
										char *s)
{
	pars->len = ft_strlen(s);
	if (pars->precision_point && pars->len > pars->precision)
		pars->len = pars->precision;
	else
		pars->precision = pars->len;
	pars->pres_len = pars->precision - pars->len;
	if (pars->len + pars->pres_len > pars->width)
		pars->width = pars->len + pars->pres_len;
	if (pars->flag_minus)
		pars->w_end = pars->width - pars->pres_len - pars->len;
	else
		pars->w_start = pars->width - pars->pres_len - pars->len;
}

static void	ft_putnstr(const char *s, int n)
{
	int	i;

	i = 0;
	while (i < n && *(s + i))
	{
		i++;
	}
	write(1, s, i);
}

int	ft_printf_type_s(t_flags *pars, va_list ap)
{
	int		i;
	char	*tmp;

	tmp = va_arg(ap, char *);
	i = 0;
	if (tmp == 0)
		tmp = "(null)";
	ft_printf_pars_s_update(pars, tmp);
	i += ft_printf_fill_char_start_end(' ', 0, pars->w_start);
	i += ft_printf_fill_char_start_end(' ', 0, pars->pres_len);
	ft_putnstr(tmp, pars->len);
	i += pars->len;
	i += ft_printf_fill_char_start_end(' ', 0, pars->w_end);
	return (i);
}

int	ft_printf_type_percent(t_flags *pars, va_list ap)
{
	unsigned char	tmp;
	int				i;

	tmp = '%';
	i = 0;
	pars->len = 1;
	if (pars->flag_zero)
		pars->pres_len = pars->width - pars->len;
	else
		pars->pres_len = 0;
	if (pars->flag_minus)
		pars->w_end = pars->width - pars->pres_len - pars->len;
	else
		pars->w_start = pars->width - pars->pres_len - pars->len;
	i += ft_printf_fill_char_start_end(' ', 0, pars->w_start);
	i += ft_printf_fill_char_start_end('0', 0, pars->pres_len);
	ft_putchar(tmp);
	i += pars->len;
	i += ft_printf_fill_char_start_end(' ', 0, pars->w_end);
	return (i);
}
