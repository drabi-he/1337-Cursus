/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:59:56 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 18:55:47 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_hex_zero(t_print *lst, size_t hex, int *len_print, int format)
{
	if (hex != 0 || lst->precision != 0)
		ft_putnbr_base((unsigned)hex, format, len_print);
	if (hex == 0 && !lst->is_p)
		ft_putnbr_base((unsigned)hex, format, len_print);
	if (hex == 0 && lst->precision == 0 && lst->is_p && lst->width > 0)
	{
		ft_putchar_fd(' ', 1);
		(*len_print)++;
	}
}

void	ft_hex_check(t_print *lst, size_t hex, int *len_print)
{
	if (lst->conversion == 'x')
	{
		if (ft_search_flag(lst->flags, '#') && hex != 0)
		{
			ft_putstr_fd("0x", 1);
			(*len_print) += 2;
		}
		ft_hex_zero(lst, hex, len_print, 0);
	}
	else
	{
		if (ft_search_flag(lst->flags, '#') && hex != 0)
		{
			ft_putstr_fd("0X", 1);
			(*len_print) += 2;
		}
		ft_hex_zero(lst, hex, len_print, 32);
	}
}
