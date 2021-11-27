/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 17:37:09 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/27 11:27:53 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void ft_print_s_with_p_minus(int width,int precision,char *c,int *len)
{
	int	i;
	int	len_print;

	i = 0;
	if (precision > (int)ft_strlen(c))
		len_print = ft_strlen(c);
	else
		len_print = precision;
	while (i < len_print)
	{
		ft_putchar_fd(c[i], 1);
		i++;
	}
	while (i < width)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (len_print > width)
		(*len) += len_print;
	else
		(*len) += width;
}

void ft_print_s_with_minus(int width,char *c,int *len)
{
	int	i;
	int	c_len;

	i = 0;
	c_len = ft_strlen(c);
	ft_putstr_fd(c,1);
	while (i < width - c_len)
	{
		ft_putchar_fd(' ',1);
		i++;
	}
	if (width > c_len)
		(*len) += width;
	else
		(*len) += c_len;
}

void ft_print_s_with_p(int width,int precision,char *c,int *len)
{
	int	i;
	int	len_print;

	i = 0;
	if (precision > (int)ft_strlen(c))
		len_print = ft_strlen(c);
	else
		len_print = precision;
	while (i < width - len_print)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	i = 0;
	while (i < len_print)
	{
		ft_putchar_fd(c[i], 1);
		i++;
	}
	if (len_print > width)
		(*len) += len_print;
	else
		(*len) += width;
}

void ft_print_s(int width,char *c,int *len)
{
	int	i;
	int	c_len;

	i = 0;
	c_len = ft_strlen(c);
	while (i < width - c_len)
	{
		ft_putchar_fd(' ',1);
		i++;
	}
	ft_putstr_fd(c,1);
	if (width > c_len)
		(*len) += width;
	else
		(*len) += c_len;
}

void	ft_print_str(char *flag,int is_p,int precision, int width, char *c, int *len)
{
	if (!c)
		c = ft_strdup("(null)");
	else
		c = ft_strdup(c);
	if (!ft_strcmp(flag,"-") || !ft_strcmp(flag,"-0"))
	{
		if (is_p)
			ft_print_s_with_p_minus(width,precision,c,len);
		else
			ft_print_s_with_minus(width,c,len);
	}
	else
	{
		if (is_p)
			ft_print_s_with_p(width,precision,c,len);
		else
			ft_print_s(width,c,len);
	}
	free(c);
	c = NULL;
}
