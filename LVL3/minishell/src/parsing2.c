/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:15:47 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/15 19:01:53 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_parse_dollar_mini(char *str, char *rst, int *i, int *j)
{
	char	*tmp;

	tmp = ft_substr(str, *j, *i - *j);
	rst = ft_strjoin2(rst, tmp);
	free (tmp);
	if (ft_isalnum(str[*i + 1]))
	{
		(*i)++;
		*j = *i;
		while (str[*i] && ft_isalnum(str[*i]))
			(*i)++;
		tmp = ft_substr(str, *j, *i - *j);
		rst = ft_strjoin2(rst, ft_get_env(g_all.env_head, tmp));
		free (tmp);
		j = i;
	}
	else if (str[*i + 1] == '?')
	{
		tmp = ft_itoa(g_all.status);
		rst = ft_strjoin2(rst, tmp);
		free(tmp);
		*j = *i + 2;
	}
	return (rst);
}

char	*ft_parse_dollar(char *str, int n)
{
	int		i;
	int		j;
	char	*rst;
	char	*tmp;

	i = 0;
	j = 0;
	rst = NULL;
	while (str[i])
	{
		if (str[i] == '$')
			rst = ft_parse_dollar_mini(str, rst, &i, &j);
		i++;
	}
	tmp = ft_substr(str, j, i - j);
	rst = ft_strjoin2(rst, tmp);
	free (tmp);
	if (n)
		free(str);
	return (rst);
}

static void	ft_node_options(t_tree **node, char *str, int i, int mode)
{
	char	*left;
	char	*right;

	left = NULL;
	if (!mode)
	{
		if (str[i] == '|')
			node[0] = ft_new_node(OR, NULL);
		if (str[i] == '&')
			node[0] = ft_new_node(AND, NULL);
		right = ft_substr_garbage(str, i + 2, ft_strlen(str));
	}
	else
	{
		node[0] = ft_new_node(PIPE, NULL);
		right = ft_substr_garbage(str, i + 1, ft_strlen(str));
	}
	if (i != 0)
		left = ft_substr_garbage(str, 0, i);
	ft_fill_tree(&node[0]->left, left, node[0]);
	ft_fill_tree(&node[0]->right, right, node[0]);
}

static void	ft_node_cmd(t_tree **node, char *str)
{
	char	**tmp;
	int		i;
	t_wild	w;

	w.i = 0;
	node[0] = ft_new_node(COMMAND, NULL);
	ft_split_red(&str, node);
	node[0]->cmd = ft_split_echo(str);
	node[0]->exist = 1;
	i = 0;
	tmp = alloc_tab(w);
	while (node[0]->cmd[i])
	{
		if (!tmp[0])
			break ;
		if (!ft_strcmp(node[0]->cmd[i], "*"))
		{
			node[0]->cmd = ft_double_join(node[0]->cmd, tmp, i);
			i = 0;
		}
		i++;
	}
	printf("%s\n", node[0]->cmd[0]);
	free_tab(tmp);
}

void	ft_fill_tree(t_tree **node, char *str, t_tree *parent)
{
	int		i;

	if (!str)
		return ;
	str = ft_strtrim(str, " ");
	i = ft_strchr_v2_0(str);
	if (i != -1)
		ft_node_options(node, str, i, 0);
	else
	{
		i = ft_strchr(str, '|');
		if (i != -1)
			ft_node_options(node, str, i, 1);
		else
		{
			if (str[0] == 40)
				ft_fill_tree(node, \
					ft_substr_garbage(str, 0, ft_strlen(str)), NULL);
			else
				ft_node_cmd(node, str);
		}
	}
	node[0]->parent = parent;
}
