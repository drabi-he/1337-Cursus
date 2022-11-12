/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:03:39 by hdrabi            #+#    #+#             */
/*   Updated: 2022/11/01 17:15:09 by hdrabi           ###   ########.fr       */
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
	g_all.status_s = 1;
	g_all.pid = fork();
	if (g_all.pid == 0)
	{
		ft_input_ouput_ctrl(root);
		if (!root->exist || (root->infile && root->ifd < 0))
		{
			g_all.status = 1;
			exit(1);
		}
		root->env = ft_list_to_array();
		execve(root->path, root->cmd, root->env);
		ft_print_error("1- MiniShell: ", root->cmd[0], ": is a directory\n");
		g_all.status = 1;
		exit(1);
	}
	close(root->ifd);
	close(root->ofd);
	wait(&g_all.status);
}

void	ft_exec_pipe(t_tree *root)
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
	if (root->infile && root->ifd < 0)
	{
		g_all.status = 1;
		exit(1);
	}
	root->env = ft_list_to_array();
	execve(root->path, root->cmd, root->env);
	ft_print_error("2- MiniShell: ", root->cmd[0], ": is a directory\n");
	g_all.status = 1;
	exit(1);
}

void	ft_exec(t_tree *root, int n)
{
	if (!root)
		return ;
	if (root->token == COMMAND && root->cmd)
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
