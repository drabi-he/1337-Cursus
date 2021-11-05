/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:24:28 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/03 13:07:25 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
int ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	if(n ==0)
		return (0);
	i = 0;
	while(s1[i] && s1[i] == s2[i] && i < n - 1)
	   i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}	
