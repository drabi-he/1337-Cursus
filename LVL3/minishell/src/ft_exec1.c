/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:03:39 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/16 18:42:56 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_parse_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != '\'')
		{
			cmd[i] = ft_substr2(cmd[i], 0, ft_strlen(cmd[i]));
			cmd[i] = ft_parse_dollar(cmd[i], 0);
		}
		else
			cmd[i] = ft_substr2(cmd[i], 0, ft_strlen(cmd[i]));
		i++;
	}
}

void	ft_input_ouput_ctrl(t_tree *root)
{
	if (root->ofd > 0)
	{
		close(1);
		dup(root->ofd);
	}
	if (root->ifd > 0)
	{
		close(0);
		dup(root->ifd);
	}
	close(root->ofd);
	close(root->ifd);
}

void	ft_exec_cmd(t_tree *root)
{
	char	**env;

	env = NULL;
	env = ft_list_to_array();
	g_all.pid = fork();
	if (g_all.pid == 0)
	{
		ft_input_ouput_ctrl(root);
		if (!root->exist || (root->infile && root->ifd < 0))
		{
			g_all.status = 1;
			exit(1);
		}
		execve(root->path, root->cmd, env);
		ft_print_error("1- MiniShell: ", root->cmd[0], ": is a directory\n");
		g_all.status = 1;
		exit(1);
	}
	close(root->ifd);
	close(root->ofd);
	wait(&g_all.status);
	// if (env[0])
	// 	free_tab(env);
}

void	ft_exec_pipe(t_tree *root)
{
	char	**env;

	if (root->ofd > 0)
	{
		close(1);
		dup(root->ofd);
	}
	if (root->ifd > 0)
	{
		close(0);
		dup(root->ifd);
	}
	if (root->infile && root->ifd < 0)
	{
		g_all.status = 1;
		exit(1);
	}
	env = ft_list_to_array();
	execve(root->path, root->cmd, env);
	ft_print_error("2- MiniShell: ", root->cmd[0], ": is a directory\n");
	g_all.status = 1;
	exit(1);
}

void	ft_exec(t_tree *root, int n)
{
	if (!root)
		return ;
	if (root->token == COMMAND)
	{
		ft_parse_cmd(root->cmd);
		if (root->is_builtin == 0)
		{
			if (n)
				ft_exec_pipe(root);
			else
				ft_exec_cmd(root);
		}
		else
			ft_exec_builtin2(root);
	}
	if (root->token == PIPE)
		run_pipeline(root);
	ft_exec_options(root);
}
