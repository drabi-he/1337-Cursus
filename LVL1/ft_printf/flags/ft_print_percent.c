/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:45:33 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 17:50:00 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_print_percent_m(int width, int *len)
{
	int	i;

	i = 0;
	ft_putchar_fd('%', 1);
	while (++i < width)
		ft_putchar_fd(' ', 1);
	(*len) += i;
}

static void	ft_print_percent_zero(int width, int *len)
{
	int	i;

	i = 0;
	while (++i < width)
		ft_putchar_fd('0', 1);
	ft_putchar_fd('%', 1);
	(*len) += i;
}

static void	ft_print_percent_sp(int width, int *len)
{
	int	i;

	i = 0;
	while (++i < width)
		ft_putchar_fd(' ', 1);
	ft_putchar_fd('%', 1);
	(*len) += i;
}

void	ft_print_percent(t_print *lst, int *len)
{
	if (ft_search_flag(lst->flags, '-'))
	{
		ft_print_percent_m(lst->width, len);
	}
	else
	{
		if (ft_search_flag(lst->flags, '0'))
		{
			ft_print_percent_zero(lst->width, len);
		}
		else
		{
			ft_print_percent_sp(lst->width, len);
		}
	}
}
