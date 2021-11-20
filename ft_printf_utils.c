/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdarrell <cdarrell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:26:56 by cdarrell          #+#    #+#             */
/*   Updated: 2021/10/15 16:23:32 by cdarrell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_fill_char_start_end(char c, int start, int end)
{
	int	i;

	i = 0;
	while (start + i < end)
	{
		ft_putchar(c);
		i++;
	}
	return (i);
}

int	ft_printf_nbrlen_ull_hex(unsigned long long int nbr, int base_len)
{
	int	len;

	len = 0;
	while (nbr || len == 0)
	{
		len++;
		nbr /= base_len;
	}
	return (len);
}

void	ft_printf_putnbr_ull_hex(unsigned long long int n, \
									char *base, int base_len)
{
	if (n >= (unsigned long long int)base_len)
		ft_printf_putnbr_ull_hex(n / base_len, base, base_len);
	ft_putchar(base[n % base_len]);
}
