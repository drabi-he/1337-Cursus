/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:31:25 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/22 11:59:13 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	cp;
	char			*str;

	if (!b)
		return (NULL);
	str = (char *)b;
	cp = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		str[i] = cp;
		i++;
	}
	return (b);
}
