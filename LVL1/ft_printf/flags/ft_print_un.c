/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_un.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:45:16 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/30 18:07:00 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void ft_print_nbr(unsigned nb,int *nb_len,int precision, int width)
{
	while(*nb_len < precision)
	{
		ft_putchar_fd('0',1);
		(*nb_len)++;
	}
	ft_putnbr_fd(nb, 1);
	while(*nb_len < width)
	{
		ft_putchar_fd(' ', 1);
		(*nb_len)++;
	}
}

void ft_un_m_pr(int width,int precision,unsigned nb,int *len)
{
	int space_count;
	int nb_len;
	space_count = width - precision;
	nb_len = ft_nbr_len(nb);
	if (nb < 0)
		ft_putchar_fd('-', 1);
	ft_print_nbr(nb,&nb_len,precision,width);
	(*len) += nb_len;
}

static void ft_print_nbr2(long long nb,int *nb_len,int precision)
{
	int i;

	i = ft_nbr_len(nb);
	while(i < precision || (nb < 0 && i - 1 < precision))
	{
		ft_putchar_fd('0',1);
		i++;
		(*nb_len)++;
	}
	ft_putnbr_fd(nb, 1);
}

void ft_un_pr(int width,int precision,unsigned nb,int *len)
{
	int space_count;
	int nb_len;
	int i;

	i = -1;
	nb_len = ft_nbr_len(nb);
	if (precision > 0)
		space_count = width - precision;
	else
		space_count = width - nb_len;
	if (nb == 0 && precision == 0)
		nb_len--;
	while(++i < space_count )
	{
		ft_putchar_fd(' ', 1);
		nb_len++;
	}
	if(nb != 0 || precision != 0)
		ft_print_nbr2(nb,&nb_len,precision);
	(*len) += nb_len;
}

void ft_print_un(char *flag,int is_p,int precision,int width,unsigned nb,int *len)
{
	if(flag[0] == '-' || flag[1] == '-')
			ft_un_m_pr(width,precision,nb,len);
	else
	{
		if (is_p)
			ft_un_pr(width,precision,nb,len);
		else
			ft_un_extra(flag,width,nb,len);
	}
}
