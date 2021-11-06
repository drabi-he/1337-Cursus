/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:28:23 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/06 12:13:36 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int		*t;
	size_t	i;

	t = (int *)malloc(count * size);
	if (!t)
		return (NULL);
	i = 0;
	while (i < count)
	{
		t[i] = 0;
		i++;
	}
	return (t);
}
