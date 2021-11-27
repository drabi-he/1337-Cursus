/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 12:30:02 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/27 17:52:50 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void ft_print_add_with_p_minus(int width,int precision,size_t addr,int *len)
{
	int i;
	int space_count;
	int len_print;

	len_print = 0;
	i = -1;
	ft_putstr_fd("0x",1);
	while (++i < precision -12)
	{
		ft_putchar_fd('0',1);
		(*len)++;
	}
	ft_putnbr_base(addr,0,&len_print);
	if (precision > 12)
		space_count = width - precision - 2;
	else
		space_count = width - 14 ;
	i = -1;
	while (++i < space_count)
	{
		ft_putchar_fd(' ',1);
		(*len)++;

	}
	(*len) += len_print + 2;
}

void ft_print_add_with_minus(int width,size_t addr,int *len)
{
	int i;
	int len_print;
	int space_count;

	i = -1;
	len_print = 0;
	ft_putstr_fd("0x",1);
	ft_putnbr_base(addr,0,&len_print);
	space_count = width - len_print - 2;
	while (++i < space_count)
		ft_putchar_fd(' ', 1);
	if (space_count >= 0)
		len_print += space_count;
	(*len) += len_print + 2;
}

void ft_print_add_with_p(int width,int precision,size_t addr,int *len)
{
	int i;
	int space_count;
	int len_print;

	len_print = 0;
	if (precision > 12)
		space_count = width - precision - 2;
	else
		space_count = width - 14 ;
	i = -1;
	while (++i < space_count)
	{
		ft_putchar_fd(' ',1);
		(*len)++;
	}
	i = -1;
	ft_putstr_fd("0x",1);
	while (++i < precision -12)
	{
		ft_putchar_fd('0',1);
		(*len)++;
	}
	ft_putnbr_base(addr,0,&len_print);
	(*len) += len_print + 2;
}

void ft_print_add(int width,size_t addr,int *len)
{
	int i;
	int len_print;
	int space_count;

	i = -1;
	len_print = 0;
	space_count = width - 14;
	while (++i < space_count)
		ft_putchar_fd(' ', 1);
	ft_putstr_fd("0x",1);
	ft_putnbr_base(addr,0,&len_print);
	if (space_count >= 0)
		len_print += space_count;
	(*len) += len_print + 2;
}

void	ft_print_ptr(char *flag,int is_p,int precision, int width, size_t addr, int *len)
{
	if (!ft_strcmp(flag,"-"))
	{
		if (is_p)
			ft_print_add_with_p_minus(width,precision,addr,len);
		else
			ft_print_add_with_minus(width,addr,len);
	}
	else
	{
		if (is_p)
			ft_print_add_with_p(width,precision,addr,len);
		else
			ft_print_add(width,addr,len);
	}
}

