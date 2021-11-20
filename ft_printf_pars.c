/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 17:03:38 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/13 20:45:35 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_pars_if(t_flags *pars)
{
	if (pars->flag_minus)
		pars->flag_zero = 0;
	if (pars->flag_plus)
		pars->flag_space = 0;
	if (pars->flag_space)
		pars->znak_value = ' ';
	if (pars->flag_plus)
		pars->znak_value = '+';
	if (pars->znak_value)
		pars->znak = 1;
}

static int	ft_printf_istype(char c)
{
	char	*type;

	type = "cspdiuxX%";
	while (*type)
	{
		if (c == *type)
			return (1);
		type++;
	}
	return (0);
}

static void	ft_printf_pars_precision(t_flags *pars, const char *s, int *i)
{
	pars->precision_point = 1;
	pars->precision = 0;
	while (ft_isdigit(*(s + *i + 1)))
	{
		*i += 1;
		pars->precision = pars->precision * 10 + *(s + *i) - '0';
	}
}

static void	ft_printf_pars_width(t_flags *pars, const char *s, int *i)
{	
	pars->width = *(s + *i) - '0';
	while (ft_isdigit(*(s + *i + 1)))
	{
		*i += 1;
		pars->width = pars->width * 10 + *(s + *i) - '0';
	}
}

int	ft_printf_pars(t_flags *pars, const char *s)
{
	int	i;

	i = 1;
	while (*(s + i) && !pars->type)
	{
		if (ft_printf_istype(*(s + i)))
			pars->type = *(s + i);
		else if (*(s + i) == '0')
			pars->flag_zero = 1;
		else if (*(s + i) == '-')
			pars->flag_minus = 1;
		else if (*(s + i) == '+')
			pars->flag_plus = 1;
		else if (*(s + i) == ' ')
			pars->flag_space = 1;
		else if (*(s + i) == '#')
			pars->flag_hash = 1;
		else if (*(s + i) == '.')
			ft_printf_pars_precision(pars, s, &i);
		else if (ft_isdigit(*(s + i)))
			ft_printf_pars_width(pars, s, &i);
		i++;
	}
	ft_printf_pars_if(pars);
	return (i);
}
