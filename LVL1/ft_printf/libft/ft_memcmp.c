/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:50:43 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/22 11:56:55 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*src1;
	char	*src2;
	size_t	i;

	if (n == 0 || !s1 || !s2)
		return (0);
	src1 = (char *)s1;
	src2 = (char *)s2;
	i = 0;
	while (src1[i] == src2[i] && i < n - 1)
		i++;
	return ((unsigned char)src1[i] - (unsigned char)src2[i]);
}
