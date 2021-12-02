/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 10:46:43 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 21:14:35 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_print_s_with_p_minus(int width, int precision,
			char *str, int *len)
{
	int	i;
	int	len_print;

	i = 0;
	if (precision > (int)ft_strlen(str))
		len_print = ft_strlen(str);
	else
		len_print = precision;
	while (i < len_print)
	{
		ft_putchar_fd(str[i], 1);
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

static void	ft_print_s_with_minus(int width, char *str, int *len)
{
	int	i;
	int	str_len;

	i = 0;
	str_len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	while (i < width - str_len)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (width > str_len)
		(*len) += width;
	else
		(*len) += str_len;
}

static void	ft_print_s_with_p(int width, int precision, char *str, int *len)
{
	int	i;
	int	len_print;

	i = 0;
	if (precision > (int)ft_strlen(str))
		len_print = ft_strlen(str);
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
		ft_putchar_fd(str[i], 1);
		i++;
	}
	if (len_print > width)
		(*len) += len_print;
	else
		(*len) += width;
}

static void	ft_print_s(int width, char *str, int *len)
{
	int	i;
	int	str_len;

	i = 0;
	str_len = ft_strlen(str);
	while (i < width - str_len)
	{
		ft_putchar_fd(' ', 1);
		i++;
	}
	ft_putstr_fd(str, 1);
	if (width > str_len)
		(*len) += width;
	else
		(*len) += str_len;
}

void	ft_print_str(t_print *lst, char *str, int *len)
{
	if (ft_search_flag(lst->flags, '-'))
	{
		if (lst->is_p)
			ft_print_s_with_p_minus(lst->width, lst->precision, str, len);
		else
			ft_print_s_with_minus(lst->width, str, len);
	}
	else
	{
		if (lst->is_p)
			ft_print_s_with_p(lst->width, lst->precision, str, len);
		else
			ft_print_s(lst->width, str, len);
	}
}
