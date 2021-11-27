/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:29:04 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/27 17:28:11 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print(size_t n, size_t size , int form,int *l)
{
	if (n > size - 1)
	{
		ft_print(n / size, size, form,l);
		n %= size;
	}
	(*l)++;
	ft_putchar(BASE[n] - form);
}

void	ft_putnbr_base(size_t nbr, int form, int *l)
{
	size_t	n;
	size_t	size;

	if (nbr < 0)
	{
		n = -nbr;
		ft_putchar('-');
	}
	else
		n = nbr;
	size = ft_strlen(BASE);
	ft_print(n, size,form,l);
}
