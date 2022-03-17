/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:47:49 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/17 13:06:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_is_builtin(t_tree *node, char *str)
{
	if (!ft_strcmp("echo", str) || !ft_strcmp("pwd", str) \
		|| !ft_strcmp("cd", str) || !ft_strcmp("unset", str) \
		|| !ft_strcmp("export", str) || !ft_strcmp("env", str) \
		|| !ft_strcmp("exit", str))
	{
		node->is_builtin = 1;
		return (1);
	}
	else
	{
		node->is_builtin = 0;
		return (0);
	}
}

static int	ft_check_access(char *tmp, t_tree **node)
{
	if (access(tmp, F_OK))
		return (1);
	else
		node[0]->path = ft_strdup_garbage(tmp);
	return (0);
}

static char	*ft_check_path(char *path, char *tmp)
{
	char	*test1;
	char	*test2;
	char	*rst;

	test1 = ft_strjoin2(path, "/");
	test2 = ft_strjoin2(test1, tmp);
	rst = NULL;
	if (!access(test2, F_OK))
	{
		rst = ft_strdup_garbage(test2);
		return (rst);
	}
	return (rst);
}

int	ft_get_path(t_tree *node, char **path)
{
	int		i;
	char	*tmp;

	tmp = ft_substr2(node->cmd[0], 0, ft_strlen(node->cmd[0]));
	if (ft_is_builtin(node, tmp) == 1)
		return (0);
	i = ft_strchr(tmp, '/');
	if (i != -1)
		return (ft_check_access(tmp, &node));
	else
	{
		if (!path)
			return (1);
		i = 0;
		while (path[i])
		{
			node->path = ft_check_path(path[i], tmp);
			if (node->path)
				return (0);
			i++;
		}
	}
	return (1);
}
