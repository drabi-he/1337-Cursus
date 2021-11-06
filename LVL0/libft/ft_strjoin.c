/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:02:56 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/06 12:55:33 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rst;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	rst = (char *)malloc((len + 1) * sizeof(char));
	if (!rst)
		return (NULL);
	i = -1;
	while (s1[++i])
		rst[i] = s1[i];
	j = -1;
	while (s2[++j])
		rst[i++] = s2[j];
	rst[i] = 0;
	return (rst);
}
