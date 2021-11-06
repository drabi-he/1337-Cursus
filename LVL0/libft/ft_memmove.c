/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:34:20 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/06 12:21:42 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	size_t	i;

	d = dst;
	s = (char *)src;
	i = -1;
	if (!dst && !src)
		return (NULL);
	if (d < s)
		while (++i < len)
			d[i] = s[i];
	else
		while (len-- > 0)
			d[len] = s[len];
	return (dst);
}
