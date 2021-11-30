/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_un_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:44:11 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/30 17:58:39 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void ft_print_nbr(int width,long long nb, int *nb_len)
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

static void ft_print_nbr2(long long nb)
{
	if(nb < 0)
		ft_putnbr_fd((unsigned)-nb,1);
	else
		ft_putnbr_fd(nb, 1);
}

void ft_un_extra(char *flag,int width,unsigned nb,int *len)
{
	int nb_len;

	nb_len = ft_nbr_len(nb);
	if (flag[0] == '0' || flag[1] == '0')
	{
		ft_print_nbr(width,nb,&nb_len);
	}
	else
	{
		while (nb_len < width)
		{
			ft_putchar_fd(' ',1);
			nb_len++;
		}
		ft_print_nbr2(nb);
	}
	(*len) += nb_len;
}
