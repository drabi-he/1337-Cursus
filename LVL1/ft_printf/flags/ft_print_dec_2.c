/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:38:14 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 15:16:52 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_sign(char *flags, int nb)
{
	if (ft_search_flag(flags, ' ')
		&& !ft_search_flag(flags, '+') && nb >= 0)
		ft_putchar_fd(' ', 1);
	if (ft_search_flag(flags, '+') && nb >= 0)
		ft_putchar_fd('+', 1);
	if (nb < 0)
		ft_putchar_fd('-', 1);
}

static void	ft_print_nbr(int width, int nb, int *nb_len)
{
	while (*nb_len < width)
	{
		ft_putchar_fd('0', 1);
		(*nb_len)++;
	}
	if (nb < 0)
		ft_putnbr_fd((unsigned)-nb, 1);
	else
		ft_putnbr_fd(nb, 1);
}

static void	ft_print_nbr2(int nb)
{
	if (nb < 0)
		ft_putnbr_fd((unsigned)-nb, 1);
	else
		ft_putnbr_fd(nb, 1);
}

void	ft_dec_extra(char *flag, int width, int nb, int *len)
{
	int	nb_len;

	nb_len = ft_nbr_len(nb);
	if ((ft_search_flag(flag, ' ') || ft_search_flag(flag, '+')) && nb >= 0)
			nb_len++;
	if (ft_search_flag(flag, '0'))
	{
		ft_print_sign(flag, nb);
		ft_print_nbr(width, nb, &nb_len);
	}
	else
	{
		while (nb_len < width)
		{
			ft_putchar_fd(' ', 1);
			nb_len++;
		}
		ft_print_sign(flag, nb);
		ft_print_nbr2(nb);
	}
	(*len) += nb_len;
}
