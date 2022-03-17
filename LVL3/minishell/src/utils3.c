/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:20:33 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/17 13:07:35 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_error(char *s1, char *s2, char *s3)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		write(2, &s1[i], 1);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		write(2, &s2[i], 1);
		i++;
	}
	i = 0;
	while (s3[i])
	{
		write(2, &s3[i], 1);
		i++;
	}
}

int	ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (ft_skip_quote_rev(s, &i) == -1)
			return (-1);
		ft_skip_par_rev(s, &i);
		if (s[i] == (char)c && s[i - 1] == (char)c)
			return (i - 1);
		i--;
	}
	return (-1);
}

int	ft_strchr_v2_0(char *str)
{
	int	i;
	int	j;

	i = ft_strrchr(str, '|');
	j = ft_strrchr(str, '&');
	if (i == -1 && j == -1)
		return (-1);
	if (i < j)
		return (j);
	else
		return (i);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	p = (char *)ft_malloc((ft_strlen(s1) + ft_strlen(s2)) + 1 * sizeof(char));
	if (!p)
		return (NULL);
	while (s1 && s1[j])
		p[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j])
		p[i++] = s2[j++];
	p[i] = 0;
	return (p);
}

t_tree	*ft_new_node(int token, char **cmd)
{
	t_tree	*new;

	new = (t_tree *)ft_malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->token = token;
	new->cmd = cmd;
	new->env = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->ifd = -2;
	new->ofd = -2;
	new->is_builtin = -1;
	new->path = NULL;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
