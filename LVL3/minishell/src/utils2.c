/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:10:46 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/15 16:26:57 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

int	ft_skip_quote(char *str, int *i)
{
	char	get;

	if (str[*i] == '\"' || str[*i] == '\'')
	{
		get = str[(*i)++];
		while (str[*i] && str[*i] != get)
			(*i)++;
		if (!str[*i])
		{
			printf("MiniShell: syntax error unclosed ");
			printf("quote near `%c'\n", str[*i]);
			return (-1);
		}
	}
	return (0);
}

void	ft_skip_par(char *str, int *i)
{
	int	cp;

	cp = 0;
	if (str[*i] == 40)
	{
		cp++;
		(*i)++;
		while (str[*i] && cp > 0)
		{
			if (str[*i] == 41)
				cp--;
			if (str[*i] == 40)
				cp++;
			(*i)++;
		}
	}
}

int	ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (ft_skip_quote(s, &i) == -1)
			return (-1);
		ft_skip_par(s, &i);
		if (s[i] == (char)c)
		{
			if (s[i + 1] == (char)c)
			{
				i += 2;
				continue ;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}
