/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 11:05:30 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/08 18:21:36 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	is_sep(const char *str, char to_find)
{
	if (*str == to_find)
		return (1);
	return (0);
}

int	str_len(const char *str, char charset)
{
	int	i;

	i = 0;
	while (str[i] && !(is_sep(str + i, charset)))
		i++;
	return (i);
}

int	count_world(const char *str, char charset)
{
	int	i;
	int	j;

	j = 0;
	while (*str)
	{
		while (*str && is_sep(str, charset))
			str++;
		i = str_len(str, charset);
		str += i;
		if (i)
			j++;
	}
	return (j);
}

char	*str_cpy(const char *str, int size)
{
	char	*t;

	t = malloc((size + 1) * sizeof(char));
	if (!t)
		return (0);
	t[size] = 0;
	while (size--)
		t[size] = str[size];
	return (t);
}

char	**ft_split(char const *s, char charset)
{
	char	**t;
	int		size;
	int		n;
	int		i;

	if (!s)
		return (NULL);
	size = count_world(s, charset);
	t = malloc ((size + 1) * sizeof(char *));
	if (!t)
		return (0);
	i = -1;
	while (++i < size)
	{
		while (*s && is_sep(s, charset))
			s++;
		n = str_len(s, charset);
		t[i] = str_cpy(s, n);
		if (!(t[i]))
			return (free(t), NULL);
		s += n;
	}
	t[size] = 0;
	return (t);
}
