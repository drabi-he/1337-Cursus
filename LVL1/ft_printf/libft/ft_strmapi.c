/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:03:57 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/22 12:29:15 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rst;
	int		i;

	if (!s || !f)
		return (NULL);
	rst = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!rst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		rst[i] = (*f)(i, s[i]);
		i++;
	}
	rst[i] = 0;
	return (rst);
}
