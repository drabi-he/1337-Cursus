/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:20:05 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/05 10:45:58 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
char *ft_strnstr(const char *haystack, const char *needle,size_t len)
{
	size_t i;
	size_t j;

	if(!needle[0])
		return ((char *)haystack);
	i = 0;
	while(haystack[i])
	{
		j = 0;
		if(haystack[i] == needle[j])
			while(haystack[i+j] == needle[j] && i + j < len)
			{
				if(!needle[j+1])
					return ((char *)(haystack + i));
				j++;
			}
		i++;
	}
	return (NULL);
}
