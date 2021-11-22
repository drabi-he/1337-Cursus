/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:13:58 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/22 12:35:12 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_index(char const *str, char const *set, int cp, int index)
{
	size_t	j;

	j = 0;
	while (str[index] && set[j])
	{
		if (str[index] == set[j])
		{
			j = 0;
			index += cp;
		}
		else
			j++;
		if (!index)
			break ;
	}
	return (index);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*rst;
	int		i;
	int		len;
	int		j;

	if (!s1)
		return (NULL);
	if (!set)
		return ((char *)s1);
	i = ft_get_index(s1, set, 1, 0);
	len = ft_get_index(s1, set, -1, ft_strlen(s1) - 1);
	if (!len)
	{
		rst = (char *)malloc(sizeof(char));
		rst[0] = 0;
		return (rst);
	}
	rst = (char *)malloc((len - i + 2) * sizeof(char));
	if (!rst)
		return (NULL);
	j = 0;
	while (i <= len)
		rst[j++] = s1[i++];
	rst[j] = 0;
	return (rst);
}
