/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:31:25 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/01 18:17:48 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	*ft_memset(void *b, int c, size_t len)
{
	size_t i;
	unsigned char cp;
	char *str;

	str = (char *)b;
	cp = (unsigned char) c;
	i = 0;
	while(i < len && str[i])
	{
		str[i]=cp;
		i++;
	}
	return (b);
}
