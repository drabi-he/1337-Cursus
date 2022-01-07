/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:04:01 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/06 19:10:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_fill_lst2(t_cmds **lst, char **av, int ac, char *path)
{
	t_cmds	*tmp;
	int		i;

	i = 2;
	while (++i < ac)
	{
		tmp = ft_new_node(av[i], path);
		ft_lstadd_back(lst, tmp);
		if (!tmp || !tmp->path)
		{
			free_list(lst[0]);
			ft_error("cmd : not found\n");
			exit(0);
		}
	}
}

void	ft_make_infile(t_all *all)
{
	char	*tmp;
	char	*join;

	if (!access(".file_tmp", F_OK))
		unlink(".file_tmp");
	all->fd[0] = open(".file_tmp", O_CREAT | O_RDWR, 0666);
	write(1, "pipe heredoc> ", 14);
	join = ft_strjoin(all->limiter, "\n");
	while (1)
	{
		tmp = get_next_line(0);
		if (!ft_strcmp(tmp, join))
		{
			free(join);
			free(tmp);
			break ;
		}
		else
		{
			ft_putstr(tmp, all->fd[0]);
			write(1, "pipe heredoc> ", 14);
		}
		free(tmp);
	}
	close(all->fd[0]);
}

int	ft_parse_heredoc(t_all *all, char **av, int ac, char **env)
{
	char	*path;

	all->limiter = ft_strdup(av[2]);
	ft_make_infile(all);
	all->fd[0] = open(".file_tmp", O_RDONLY, 0666);
	all->fd[1] = open(av[ac], O_CREAT, 0666);
	close(all->fd[1]);
	all->fd[1] = open(av[ac], O_RDWR | O_APPEND);
	if (pipe(all->p) == -1)
		ft_error(NULL);
	all->head = NULL;
	path = ft_get_path_line(env);
	ft_fill_lst2(&all->head, av, ac, path);
	return (0);
}

void	ft_exec2(t_all all, char **env)
{
	all.fork[0] = fork();
	if (all.fork[0] < 0)
		ft_error(NULL);
	if (!all.fork[0])
	{
		dup2(all.p[1], STDOUT_FILENO);
		dup2(all.fd[0], 0);
		close(all.p[0]);
		close(all.p[1]);
		execve(all.head->path, all.head->cmd, env);
	}
	all.fork[1] = fork();
	if (all.fork[1] < 0)
		ft_error(NULL);
	if (!all.fork[1])
	{
		dup2(all.p[0], STDIN_FILENO);
		dup2(all.fd[1], 1);
		close(all.p[0]);
		close(all.p[1]);
		execve(all.head->next->path, all.head->next->cmd, env);
	}
	waitpid(all.fork[0], NULL, 0);
	free(all.limiter);
}
