/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_addr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:30:14 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 17:22:47 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_print_add_with_p_minus(int width, int precision,
			size_t addr, int *len)
{
	int	i;
	int	space_count;
	int	len_print;

	len_print = 0;
	i = -1;
	ft_putstr_fd("0x", 1);
	while (++i < precision - 12)
	{
		ft_putchar_fd('0', 1);
		(*len)++;
	}
	ft_putnbr_base(addr, 0, &len_print);
	if (precision > 12)
		space_count = width - precision - 2;
	else
		space_count = width - 14 ;
	i = -1;
	while (++i < space_count)
	{
		ft_putchar_fd(' ', 1);
		(*len)++;
	}
	(*len) += len_print + 2;
}

static void	ft_print_add_with_minus(int width, size_t addr, int *len)
{
	int	i;
	int	len_print;
	int	space_count;

	i = -1;
	len_print = 0;
	ft_putstr_fd("0x", 1);
	ft_putnbr_base(addr, 0, &len_print);
	space_count = width - len_print - 2;
	while (++i < space_count)
		ft_putchar_fd(' ', 1);
	if (space_count >= 0)
		len_print += space_count;
	(*len) += len_print + 2;
}

static void	ft_print_add_with_p(int width, int precision, size_t addr, int *len)
{
	int	i;
	int	space_count;
	int	len_print;

	len_print = 0;
	space_count = ft_ptr_null(precision, width, addr);
	i = -1;
	while (++i < space_count)
	{
		ft_putchar_fd(' ', 1);
		(*len)++;
	}
	i = -1;
	ft_putstr_fd("0x", 1);
	while (++i < precision - 12)
	{
		ft_putchar_fd('0', 1);
		(*len)++;
	}
	if (addr != 0)
		ft_putnbr_base(addr, 0, &len_print);
	(*len) += len_print + 2;
}

static void	ft_print_add(int width, size_t addr, int *len)
{
	int	i;
	int	len_print;
	int	space_count;

	i = -1;
	len_print = 0;
	space_count = width - ft_convert_len(addr) - 2;
	while (++i < space_count)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd("0x", 1);
	ft_putnbr_base(addr, 0, &len_print);
	if (space_count >= 0)
		len_print += space_count;
	(*len) += len_print + 2;
}

void	ft_print_ptr(t_print *lst, size_t addr, int *len)
{
	if (ft_search_flag(lst->flags, '-'))
	{
		if (lst->is_p)
			ft_print_add_with_p_minus(lst->width, lst->precision, addr, len);
		else
			ft_print_add_with_minus(lst->width, addr, len);
	}
	else
	{
		if (lst->is_p)
			ft_print_add_with_p(lst->width, lst->precision, addr, len);
		else
			ft_print_add(lst->width, addr, len);
	}
}
