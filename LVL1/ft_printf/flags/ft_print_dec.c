/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 11:47:44 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/30 17:53:45 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void ft_print_nbr(int nb,int *nb_len,int precision, int width)
{
	while(*nb_len < precision || (nb < 0 && *nb_len - 1 < precision))
	{
		ft_putchar_fd('0',1);
		(*nb_len)++;
	}
	if(nb < 0)
	ft_putnbr_fd((unsigned)-nb,1);
	else
	ft_putnbr_fd(nb, 1);
	while(*nb_len < width)
	{
		ft_putchar_fd(' ', 1);
		(*nb_len)++;
	}
}

void ft_dec_m_pr(char *flag,int width,int precision,int nb, int *len)
{
	int space_count;
	int nb_len;

	space_count = width - precision;
	nb_len = ft_nbr_len(nb);
	if((flag[0] == '+' || flag[1] == '+') && nb >=0)
	{
		ft_putchar_fd('+',1);
		nb_len++;
	}
	if ((flag[0] == ' ' || flag[1] == ' ') && nb >= 0)
	{
		ft_putchar_fd(' ',1);
		nb_len++;
	}
	if (nb < 0)
		ft_putchar_fd('-', 1);
	ft_print_nbr(nb,&nb_len,precision,width);
	(*len) += nb_len;
}

static void ft_print_nbr2(int nb,int *nb_len,int precision)
{
	int i;

	i = ft_nbr_len(nb);
	while(i < precision || (nb < 0 && i - 1 < precision))
	{
		ft_putchar_fd('0',1);
		i++;
		(*nb_len)++;
	}
	if(nb < 0)
	ft_putnbr_fd((unsigned)-nb,1);
	else
	ft_putnbr_fd(nb, 1);
}

void ft_dec_pr(char *flag,int width,int precision,int nb, int *len)
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
	if((flag[0] == '+' || flag[1] == '+' || flag[0] == ' ' || flag[1] == ' ') && nb >=0)
	{
		nb_len++;
		space_count--;
	}
	while(++i < space_count )
	{
		ft_putchar_fd(' ', 1);
		nb_len++;
	}
	if ((flag[0] == ' ' || flag[1] == ' ') && nb >= 0)
		ft_putchar_fd(' ',1);
	if ((flag[0] == '+' || flag[1] == '+') && nb >= 0)
		ft_putchar_fd('+',1);
	if (nb < 0)
		ft_putchar_fd('-', 1);
	ft_print_nbr2(nb,&nb_len,precision);
	(*len) += nb_len;
}

void ft_print_dec(char *flag,int is_p,int precision,int width,int nb,int *len)
{
	if(flag[0] == '-' || flag[1] == '-')
			ft_dec_m_pr(flag,width,precision,nb,len);
	else
	{
		if (is_p)
			ft_dec_pr(flag,width,precision,nb,len);
		else
			ft_dec_extra(flag,width,nb,len);
	}
}
