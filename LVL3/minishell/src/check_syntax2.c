/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:21:06 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/15 14:36:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_valid_parenthesis_mini(char *str, int *i, int *cp)
{
	int	tmp;

	tmp = 0;
	while (str[*i] && *cp > 0)
	{
		if (str[*i] == '&' || str[*i] == '|')
			tmp++;
		if (str[*i] == 40)
			(*cp)++;
		if (str[*i] == 41)
			(*cp)--;
		if (*cp)
			(*i)++;
	}
	if (tmp)
		return (1);
	return (0);
}

int	ft_valid_parenthesis_norm(char *str, int *i, int *cp)
{
	if (str[*i] == 40)
	{
		(*cp)++;
		(*i)++;
		if (!ft_valid_parenthesis_mini(str, i, cp))
		{
			printf ("MiniShell: syntax error near ");
			printf("unexpected token `%c'\n", str[*i]);
			return (1);
		}
	}
	if (*cp != 0)
	{
		printf ("MiniShell: syntax error near ");
		printf("unexpected token `%c'\n", str[*i]);
		return (1);
	}
	return (0);
}

int	ft_valid_parenthesis(char *str)
{
	int	i;
	int	cp;

	i = 0;
	cp = 0;
	while (str[i])
	{
		if (ft_skip_quote(str, &i) == -1)
			return (1);
		if (str[i] == 41)
		{
			printf ("MiniShell: syntax error near ");
			printf("unexpected token `%c'\n", str[i]);
			return (1);
		}
		if (ft_valid_parenthesis_norm(str, &i, &cp))
			return (1);
		i++;
	}
	return (0);
}
