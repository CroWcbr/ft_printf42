/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 16:03:52 by cdarrell          #+#    #+#             */
/*   Updated: 2021/11/03 19:46:40 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_before_percent(t_ft_printf_set *fp)
{
	int	len;

	len = 0;
	while (*(fp->format + len) && *(fp->format + len) != '%')
		len++;
	write(1, fp->format, len);
	fp->format += len;
	fp->len += len;
}

static void	ft_printf_pars_init(t_flags *pars)
{
	pars->flag_minus = 0;
	pars->flag_zero = 0;
	pars->precision_point = 0;
	pars->precision = 0;
	pars->width = 0;
	pars->flag_hash = 0;
	pars->flag_space = 0;
	pars->flag_plus = 0;
	pars->type = '\0';
	pars->znak = 0;
	pars->znak_value = '\0';
	pars->w_start = 0;
	pars->pres_len = 0;
	pars->len = 0;
	pars->w_end = 0;
}

static void	ft_printf_choice_type(t_ft_printf_set *fp)
{
	if (fp->pars->type == 'c')
		fp->len += ft_printf_type_c(fp->pars, fp->ap);
	else if (fp->pars->type == 's')
		fp->len += ft_printf_type_s(fp->pars, fp->ap);
	else if (fp->pars->type == 'p')
		fp->len += ft_printf_type_p(fp->pars, fp->ap);
	else if (fp->pars->type == 'd' || fp->pars->type == 'i')
		fp->len += ft_printf_type_d_i_u(fp->pars, fp->ap);
	else if (fp->pars->type == 'u')
		fp->len += ft_printf_type_d_i_u(fp->pars, fp->ap);
	else if (fp->pars->type == 'x' || fp->pars->type == 'X')
		fp->len += ft_printf_type_x(fp->pars, fp->ap);
	else if (fp->pars->type == '%')
		fp->len += ft_printf_type_percent(fp->pars, fp->ap);
}

static void	ft_printf_percent(t_ft_printf_set *fp)
{
	int		len;
	t_flags	pars;

	fp->pars = &pars;
	ft_printf_pars_init(fp->pars);
	len = ft_printf_pars(fp->pars, fp->format);
	if (pars.type)
		ft_printf_choice_type(fp);
	fp->format += len;
}

int	ft_printf(const char *format, ...)
{
	t_ft_printf_set	fp;

	fp.format = format;
	fp.len = 0;
	va_start(fp.ap, format);
	while (*fp.format)
	{
		ft_printf_before_percent(&fp);
		if (*fp.format == '%')
			ft_printf_percent(&fp);
	}
	va_end(fp.ap);
	return (fp.len);
}
