/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:56:26 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/03 17:02:15 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strchr(const char *s, int c)
{
	int i;

	if((char)c == '\0')
		return ((char *)(s + ft_strlen(s)));
	i = 0;
	while(s[i])
	{
		if(s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}
