/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dec_multi_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:26:40 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/30 15:45:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_sign(char *flag,int nb)
{
	if((flag[0] == '+' || flag[1] == '+') && nb >= 0)
		ft_putchar_fd('+', 1);
	if((flag[0] == ' ' || flag[1] == ' ') && nb >= 0)
		ft_putchar_fd(' ', 1);
	if (nb < 0)
		ft_putchar_fd('-', 1);
}

static void ft_print_nbr(int width,int nb, int *nb_len)
{
	while (*nb_len < width)
	{
		ft_putchar_fd('0',1);
		(*nb_len)++;
	}

	if(nb < 0)
		ft_putnbr_fd((unsigned)-nb,1);
	else
		ft_putnbr_fd(nb, 1);
}

static void ft_print_nbr2(int nb)
{
	if(nb < 0)
		ft_putnbr_fd((unsigned)-nb,1);
	else
		ft_putnbr_fd(nb, 1);
}

void	ft_dec_extra(char *flag,int width,int nb,int *len)
{
	int nb_len;

	nb_len = ft_nbr_len(nb);
	if((flag[0] == '+' || flag[1] == '+' || flag[0] == ' ' || flag[1] == ' ') && nb >= 0)
			nb_len++;
	if (flag[0] == '0' || flag[1] == '0')
	{
		ft_print_sign(flag,nb);
		ft_print_nbr(width,nb,&nb_len);
	}
	else
	{
		while (nb_len < width)
		{
			ft_putchar_fd(' ',1);
			nb_len++;
		}
		ft_print_sign(flag,nb);
		ft_print_nbr2(nb);
	}
	(*len) += nb_len;
}
