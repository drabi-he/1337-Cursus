/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:01:12 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/17 13:07:52 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **t)
{
	int	i;

	i = 0;
	while (t && t[i])
	{
		if (t[i])
			free(t[i]);
		i++;
	}
	if (t)
		free(t);
}

void	ft_sub_len(char *s, unsigned int start, size_t *len)
{
	char	get;
	int		cp;
	int		i;

	i = 0;
	get = '\0';
	cp = 0;
	if (ft_strlen(s + start) < *len)
		*len = ft_strlen(s + start);
	while (i < (int)*len)
	{
		if ((s[start + i] == '\'' || s[start + i] == '\"') && cp % 2 == 0)
			get = s[start + i];
		if (s[start + i] == get)
			cp++;
		i++;
	}
	*len -= cp;
}

static char	*ft_substr2_norm(char *s, int start, size_t len)
{
	char	*p;

	if (!s || start < 0)
		return (NULL);
	ft_sub_len(s, start, &len);
	if (ft_strlen(s) <= (size_t)start)
		return (NULL);
	p = (char *)ft_malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	return (p);
}

static void	ft_gfy_norm(size_t *i, size_t *j, int *cp)
{
	*i = 0;
	*j = 0;
	*cp = 0;
}

char	*ft_substr2(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*p;
	char	get;
	int		cp;

	p = ft_substr2_norm(s, start, len);
	if (!p)
		return (NULL);
	ft_gfy_norm(&i, &j, &cp);
	while (j < len)
	{
		if ((s[start + i] == '\'' || s[start + i] == '\"') && cp % 2 == 0)
			get = s[start + i];
		if (s[start + i] == get)
		{
			cp++;
			i++;
		}
		else
			p[j++] = s[start + i++];
	}
	p[j] = 0;
	return (p);
}
