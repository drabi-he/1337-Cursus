/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:35:26 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/03 13:17:47 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src,size_t dstsize)
{
	
	size_t	i;
	size_t dest_size;

	dest_size = ft_strlen(dst);
	if (dstsize - dest_size <= 0)
		return (dstsize+ft_strlen(src));
	i = 0;
	while (src[i] && (dest_size + i) < dstsize - 1)
	{
		dst[dest_size + i] = src[i];
		i++;
	}
	dst[dest_size + i] = '\0';
	return (ft_strlen(src)+dest_size);
}
