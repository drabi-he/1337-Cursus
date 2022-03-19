/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:40:37 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/19 18:22:18 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_check_tree(t_tree *root)
{
	if (!root)
		return (0);
	if (root->token == PIPE || root->token == OR || root->token == AND)
	{
		if (!root->right || !root->left)
			return (1);
	}
	ft_check_tree(root->right);
	ft_check_tree(root->left);
	return (0);
}

static int	ft_check_tree2(t_tree *root, char **path)
{
	if (!root)
		return (0);
	if (root->token == COMMAND && !root->cmd)
		return (1);
	if (root->token == COMMAND && root->cmd[0])
	{
		if (ft_get_path(root, path))
		{
			ft_print_error("MiniShell: ", root->cmd[0], ": command not found\n");
			root->exist = 0;
			return (1);
		}
	}
	ft_check_tree2(root->right, path);
	ft_check_tree2(root->left, path);
	return (0);
}

void	ft_tree_init(char *str)
{
	char	*tmp;
	char	**paths;

	g_all.root = NULL;
	g_all.g_head = NULL;
	str = ft_strtrim(str, WHITESPACE);
	ft_fill_tree(&g_all.root, str, NULL);
	if (ft_check_tree(g_all.root))
	{
		printf("MiniShell: syntax error\n");
		return ;
	}
	tmp = ft_get_env(g_all.env_head, "PATH");
	paths = ft_split(tmp, ':');
	ft_check_tree2(g_all.root, paths);
	free_tab(paths);
	ft_exec(g_all.root, 0);
}
