/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 18:01:04 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/22 11:17:38 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_alloc(ssize_t n)
{
	ssize_t	i;

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

char	*ft_itoa(ssize_t n)
{
	char			*rst;
	ssize_t				size;
	size_t	nb;

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
