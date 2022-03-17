/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 14:14:55 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/17 12:20:36 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exec_options(t_tree *root)
{
	if (root->token == AND)
	{
		ft_exec(root->left, 0);
		if (g_all.status == 0)
			ft_exec(root->right, 0);
	}
	if (root->token == OR)
	{
		ft_exec(root->left, 0);
		if (g_all.status != 0)
			ft_exec(root->right, 0);
	}
}

pid_t	run_pipe(t_tree *root, int fds[2], int side)
{
	int			end;
	int			fileno;
	t_tree		*cmdtree;

	end = 1;
	fileno = STDOUT_FILENO;
	cmdtree = root->left;
	if (side & 2)
	{
		end = 0;
		fileno = STDIN_FILENO;
		cmdtree = root->right;
	}
	g_all.pid = fork();
	if (g_all.pid == 0)
	{
		dup2(fds[end], fileno);
		close(fds[0]);
		close(fds[1]);
		ft_exec(cmdtree, 1);
		exit(0);
	}
	return (g_all.pid);
}

void	run_pipeline(t_tree *root)
{
	int	status;
	int	pids[2];
	int	fds[2];

	if (pipe(fds) == -1)
		return ;
	pids[0] = run_pipe(root, fds, 1);
	if (pids[0] == -1)
		return ;
	pids[1] = run_pipe(root, fds, 2);
	if (pids[1] == -1)
		return ;
	close(fds[0]);
	close(fds[1]);
	wait(&status);
	wait(&status);
}

void	ft_exec_builtin2(t_tree *root)
{
	int	out;

	out = dup(1);
	if (root->ofd > 0)
	{
		close(1);
		dup(root->ofd);
	}
	ft_exec_builtin(root);
	dup2(out, 1);
}

void	ft_exec_builtin(t_tree *root)
{
	if (!ft_strcmp(root->cmd[0], "cd"))
		g_all.status = ft_cd(g_all.env_head, root->cmd[1]);
	if (!ft_strcmp(root->cmd[0], "pwd"))
		g_all.status = ft_pwd();
	if (!ft_strcmp(root->cmd[0], "env"))
		g_all.status = ft_env(g_all.env_head);
	if (!ft_strcmp(root->cmd[0], "echo"))
		g_all.status = ft_echo(1, root->cmd);
	if (!ft_strcmp(root->cmd[0], "unset"))
		g_all.status = ft_unset(&g_all.env_head, root->cmd[1]);
	if (!ft_strcmp(root->cmd[0], "export"))
		g_all.status = ft_export(root->cmd[1], g_all.env_head, 0);
	if (!ft_strcmp(root->cmd[0], "exit"))
		ft_exit(root->cmd);
	if (root->parent && root->parent->token == PIPE)
		exit(0);
}
