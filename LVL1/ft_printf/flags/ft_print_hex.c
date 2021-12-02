/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:49:54 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 17:43:58 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_print_add_with_p_minus(t_print *lst, size_t hex, int *len)
{
	int	i;
	int	space_count;
	int	len_print;

	len_print = 0;
	i = -1;
	while (++i < lst->precision - ft_convert_len(hex))
	{
		ft_putchar_fd('0', 1);
		(*len)++;
	}
	ft_hex_check(lst, hex, &len_print);
	if (lst->precision >= ft_convert_len(hex))
		space_count = lst->width - lst->precision;
	else
		space_count = lst->width - ft_convert_len(hex);
	i = -1;
	while (++i < space_count)
	{
		ft_putchar_fd(' ', 1);
		(*len)++;
	}
	(*len) += len_print;
}

static void	ft_print_add_with_minus(t_print *lst, size_t hex, int *len)
{
	int	i;
	int	len_print;
	int	space_count;

	i = -1;
	len_print = 0;
	ft_hex_check(lst, hex, &len_print);
	space_count = lst->width - len_print;
	while (++i < space_count)
		ft_putchar_fd(' ', 1);
	if (space_count >= 0)
		len_print += space_count;
	(*len) += len_print;
}

static void	ft_print_add_with_p(t_print *lst, size_t hex, int *len)
{
	int	i;
	int	space_count;
	int	len_print;

	len_print = 0;
	if (lst->precision >= ft_convert_len(hex))
		space_count = lst->width - lst->precision;
	else
		space_count = lst->width - ft_convert_len(hex);
	i = -1;
	while (++i < space_count)
	{
		ft_putchar_fd(' ', 1);
		(*len)++;
	}
	i = -1;
	while (++i < lst->precision - ft_convert_len(hex))
	{
		ft_putchar_fd('0', 1);
		(*len)++;
	}
	ft_hex_check(lst, hex, &len_print);
	(*len) += len_print ;
}

static void	ft_print_hexa(t_print *lst, size_t hex, int *len)
{
	int	i;
	int	len_print;
	int	space_count;

	i = -1;
	len_print = 0;
	space_count = lst->width - ft_convert_len(hex);
	if (ft_search_flag(lst->flags, '0'))
		while (++i < space_count)
			ft_putchar_fd('0', 1);
	else
		while (++i < space_count)
			ft_putchar_fd(' ', 1);
	ft_hex_check(lst, hex, &len_print);
	if (space_count >= 0)
		len_print += space_count;
	(*len) += len_print;
}

void	ft_print_hex(t_print *lst, size_t hex, int *len)
{
	if (ft_search_flag(lst->flags, '-'))
	{
		if (lst->is_p)
			ft_print_add_with_p_minus(lst, hex, len);
		else
			ft_print_add_with_minus(lst, hex, len);
	}
	else
	{
		if (lst->is_p)
			ft_print_add_with_p(lst, hex, len);
		else
			ft_print_hexa(lst, hex, len);
	}
}
