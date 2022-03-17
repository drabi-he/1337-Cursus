/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:44:57 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/17 11:04:25 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	**ft_malloc(int alloc)
{
	void	**ptr;

	ptr = (void **)malloc(alloc);
	if (!ptr)
		return (printf("failed allocation"), exit(1), NULL);
	ft_add_garbage(&g_all.g_head, ft_new_garbage(ptr));
	return (ptr);
}

static int	ft_get_index(char *str, char *set, int cp, int index)
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

char	*ft_strtrim(char *s1, char *set)
{
	char	*rst;
	int		i;
	int		len;
	int		j;

	if (!s1)
		return (NULL);
	i = ft_get_index(s1, set, 1, 0);
	len = ft_get_index(s1, set, -1, ft_strlen(s1) - 1);
	if (len <= 0 && s1[0] == ' ')
		return (NULL);
	rst = (char *)ft_malloc((len - i + 2) * sizeof(char));
	if (!rst)
		return (NULL);
	j = 0;
	while (i <= len)
		rst[j++] = s1[i++];
	rst[j] = 0;
	return (rst);
}

static void	ft_recalculate_len(char **str, unsigned int *start, size_t *len)
{
	int	cp;
	int	i;

	i = *start;
	cp = 0;
	str[0] = ft_strtrim(str[0], " ");
	(*len)--;
	while (str[0][*len] == ' ')
		(*len)--;
	if (str[0][*len] == 41 && str[0][0] == 40)
	{
		while ((size_t)i < *len)
		{
			ft_skip_par(str[0], &i);
			if (ft_strchr(TABLE, str[0][i]) != -1)
			{
				(*len)++;
				return ;
			}
			i++;
		}
		(*len) -= 2;
		(*start)++;
	}
	(*len)++;
}

char	*ft_substr_garbage(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	ft_recalculate_len(&s, &start, &len);
	if (!s || start < 0)
		return (NULL);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	if (ft_strlen(s) <= start)
		return (NULL);
	p = (char *)ft_malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = 0;
	return (p);
}
