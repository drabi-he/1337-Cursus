/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:05:05 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/26 17:06:55 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_char(char *flag,int width, char c, int *len)
{
	int i;

	i = -1;
	if (!ft_strcmp(flag,"-"))
	{
		ft_putchar_fd(c, 1);
		while (++i < width - 1)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (++i < width - 1)
			ft_putchar_fd(' ', 1);
		ft_putchar_fd(c, 1);
	}
	if (width == 0)
		(*len)++;
	else
		(*len) += width;
}
