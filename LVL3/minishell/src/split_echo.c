/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:17:05 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/17 12:58:17 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_sub_len2(char *s, unsigned int start, size_t *len)
{
	if (ft_strlen(s + start) < *len)
		*len = ft_strlen(s + start);
}

static char	*ft_substr3(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*p;
	int		cp;

	if (!s || start < 0)
		return (NULL);
	ft_sub_len2(s, start, &len);
	if (ft_strlen(s) <= start)
		return (NULL);
	p = (char *)ft_malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	cp = 0;
	while (j < len)
		p[j++] = s[start + i++];
	p[j] = 0;
	return (p);
}

static void	ft_count_words(char *str, int *j)
{
	int		i;
	int		k;
	char	get;

	i = -1;
	while (str[++i])
	{
		k = 0;
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				get = str[i++];
				while (str[i] && str[i] != get)
					i++;
			}
			k++;
			i++;
		}
		if (k)
			(*j)++;
	}
}

static void	ft_cpyyy(char *str, char ***t, int j)
{
	int		i;
	int		len;
	char	get;

	i = -1;
	while (str[++i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		len = i;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				get = str[i++];
				while (str[i] && str[i] != get)
					i++;
			}
			i++;
		}
		t[0][j] = ft_substr3(str, len, i - len);
		j++;
	}
	t[0][j] = 0;
}

char	**ft_split_echo(char *str)
{
	int		j;
	char	**t;

	j = 0;
	ft_count_words(str, &j);
	t = (char **)ft_malloc((j + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	ft_cpyyy(str, &t, 0);
	return (t);
}
