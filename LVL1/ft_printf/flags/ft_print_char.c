/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:53:50 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 11:18:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_print_char(t_print *node, char c, int *len)
{
	int	i;

	i = -1;
	if (ft_search_flag(node->flags, '-'))
	{
		ft_putchar_fd(c, 1);
		while (++i < node->width - 1)
			ft_putchar_fd(' ', 1);
	}
	else
	{
		while (++i < node->width - 1)
			ft_putchar_fd(' ', 1);
		ft_putchar_fd(c, 1);
	}
	if (node->width == 0)
		(*len)++;
	else
		(*len) += node->width;
}
