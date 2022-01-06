/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:00:45 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/06 17:59:57 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_fill_lst(t_cmds **lst, char **av, int ac, char *path)
{
	t_cmds	*tmp;
	int		i;

	i = 1;
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

char	*ft_get_path_line(char **env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		tmp = ft_strnstr(env[i], "PATH=", 5);
		if (tmp)
			return (tmp);
		i++;
	}
	return (tmp);
}

void	ft_parse_args(t_all *all, char **av, int ac, char **env)
{
	char	*path;

	if (access(av[1], F_OK))
		ft_error(NULL);
	all->fd[0] = open(av[1], O_RDWR | S_IRUSR, S_IWUSR);
	if (!access(av[ac], F_OK))
		unlink(av[ac]);
	all->fd[1] = open(av[ac], O_CREAT, 0666);
	close(all->fd[1]);
	all->fd[1] = open(av[ac], O_RDWR);
	if (pipe(all->p) == -1)
		ft_error(NULL);
	all->head = NULL;
	path = ft_get_path_line(env);
	ft_fill_lst(&all->head, av, ac, path);
}

void	ft_mini_exec(t_all all, int *fd_in, int i, char **env)
{
	dup2(*fd_in, 0);
	if (all.head->next)
	{
		dup2(all.p[1], 1);
		if (!i)
			dup2(all.fd[0], 0);
	}
	if (!all.head->next)
		dup2(all.fd[1], 1);
	close(all.p[0]);
	execve(all.head->path, all.head->cmd, env);
	exit(0);
}

void	ft_exec(t_all all, char **env)
{
	int	fd_in;
	int	i;

	i = 0;
	fd_in = 0;
	while (all.head)
	{
		pipe(all.p);
		all.fork[0] = fork();
		if (all.fork[0] == -1)
			exit(0);
		else if (all.fork[0] == 0)
		{
			ft_mini_exec(all, &fd_in, i, env);
		}
		else
		{
			wait(NULL);
			close(all.p[1]);
			fd_in = all.p[0];
			all.head = all.head->next;
			i++;
		}
	}
}
