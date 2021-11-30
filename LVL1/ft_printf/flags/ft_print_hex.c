/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:12:15 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/30 19:03:14 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void ft_print_add_with_p_minus(int width,int precision,size_t hex,int *len,char conversion)
{
	int i;
	int space_count;
	int len_print;

	len_print = 0;
	i = -1;
	while (++i < precision -12)
	{
		ft_putchar_fd('0',1);
		(*len)++;
	}
	if (conversion == 'x')
		ft_putnbr_base((unsigned)hex,0,&len_print);
	else
		ft_putnbr_base((unsigned)hex,32,&len_print);
	if (precision > 12)
		space_count = width - precision;
	else
		space_count = width - 14 ;
	i = -1;
	while (++i < space_count)
	{
		ft_putchar_fd(' ',1);
		(*len)++;
	}
	(*len) += len_print;
}

static void ft_print_add_with_minus(int width,size_t hex,int *len,char conversion)
{
	int i;
	int len_print;
	int space_count;

	i = -1;
	len_print = 0;
	if (conversion == 'x')
		ft_putnbr_base((unsigned)hex,0,&len_print);
	else
		ft_putnbr_base((unsigned)hex,32,&len_print);
	space_count = width - len_print;
	while (++i < space_count)
		ft_putchar_fd(' ', 1);
	if (space_count >= 0)
		len_print += space_count;
	(*len) += len_print;
}

static void ft_print_add_with_p(int width,int precision,size_t hex,int *len,char conversion)
{
	int i;
	int space_count;
	int len_print;

	len_print = 0;
	space_count = ft_ptr_null(precision,width,hex);
	i = -1;
	while (++i < space_count)
	{
		ft_putchar_fd(' ',1);
		(*len)++;
	}
	i = -1;
	while (++i < precision - ft_convert_len(hex))
	{
		ft_putchar_fd('0',1);
		(*len)++;
	}
	if (conversion == 'x')
		ft_putnbr_base((unsigned)hex,0,&len_print);
	else
		ft_putnbr_base((unsigned)hex,32,&len_print);
	(*len) += len_print ;
}

static void ft_print_hexa(char *flag,int width,size_t hex,int *len,char conversion)
{
	int i;
	int len_print;
	int space_count;

	i = -1;
	len_print = 0;
	space_count = width - ft_convert_len(hex);
	if (flag[0] == '0' || flag[1] == '0')
	while (++i < space_count)
		ft_putchar_fd('0', 1);
	else
	while (++i < space_count)
		ft_putchar_fd(' ', 1);
	if (conversion == 'x')
		ft_putnbr_base((unsigned)hex,0,&len_print);
	else
		ft_putnbr_base((unsigned)hex,32,&len_print);
	if (space_count >= 0)
		len_print += space_count;
	(*len) += len_print;
}

void	ft_print_hex(char conversion,char *flag,int is_p,int precision, int width, size_t hex, int *len)
{
	if (!ft_strcmp(flag,"-"))
	{
		if (is_p)
			ft_print_add_with_p_minus(width,precision,hex,len,conversion);
		else
			ft_print_add_with_minus(width,hex,len,conversion);
	}
	else
	{
		if (is_p)
			ft_print_add_with_p(width,precision,hex,len,conversion);
		else
			ft_print_hexa(flag,width,hex,len,conversion);
	}
}
