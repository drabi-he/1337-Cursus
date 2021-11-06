/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:01:04 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/06 12:15:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_alloc(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*rst;
	int				size;
	unsigned int	nb;

	size = ft_alloc(n) + 1;
	rst = (char *)malloc(size * sizeof(char));
	if (!rst)
		return (NULL);
	if (n < 0)
		nb = -n;
	else
		nb = n;
	rst[--size] = 0;
	while (--size >= 0 && nb)
	{
		rst[size] = '0' + nb % 10;
		nb /= 10;
	}
	if (n < 0)
		rst[0] = '-';
	if (n == 0)
		rst[0] = '0';
	return (rst);
}
