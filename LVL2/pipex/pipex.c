/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:11:20 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/06 14:10:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_cmds
{
	char			**cmd;
	char			*path;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_all
{
	t_cmds	*head;
	int		p[2];
	int		fd[2];
}	t_all;

//utils
void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_error(char *msg)
{
	if (msg)
		ft_putstr(msg);
	else
		perror("Error ");
	exit(0);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s)
		return (NULL);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	if (ft_strlen(s) <= start)
		len = 0;
	p = (char *)malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (i < len)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = 0;
	return (p);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!needle[0])
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j] && i + j < len)
			{
				if (!needle[j + 1])
					return ((char *)(haystack + i));
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rst;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	rst = (char *)malloc((len + 1) * sizeof(char));
	if (!rst)
		return (NULL);
	i = -1;
	while (s1[++i])
		rst[i] = s1[i];
	j = -1;
	while (s2[++j])
		rst[i++] = s2[j];
	rst[i] = 0;
	return (rst);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;

	copy = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

int	str_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s && (*s++ != c))
		i++;
	return (i);
}

void	free_tab(char **t)
{
	int	i;

	i = 0;
	while (t[i])
		free(t[i++]);
	free(t);
}

int	count_world(const char *s, char c)
{
	int	i;
	int	j;

	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		i = str_len(s, c);
		s += i;
		if (i)
			j++;
	}
	return (j);
}

char	*str_cpy(const char *s, int size)
{
	char	*t;

	t = malloc((size + 1) * sizeof(char));
	if (!t)
		return (0);
	t[size] = 0;
	while (size--)
		t[size] = s[size];
	return (t);
}

char	**ft_split(char const *s, char c)
{
	char	**t;
	int		size;
	int		n;
	int		i;

	if (!s)
		return (NULL);
	size = count_world(s, c);
	t = malloc ((size + 1) * sizeof(char *));
	if (!t)
		return (0);
	i = -1;
	while (++i < size)
	{
		while (*s && *s == c)
			s++;
		n = str_len(s, c);
		t[i] = str_cpy(s, n);
		if (!(t[i]))
			return (free_tab(t), NULL);
		s += n;
	}
	t[size] = 0;
	return (t);
}

char	*ft_get_path(char *cmd, char *path)
{
	char	**tmp;
	char	*sub;
	char	*join;
	char	*test;
	int		i;

	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	sub = ft_substr(path, 5 , 1000);
	tmp = ft_split(sub, ':');
	free(sub);
	i = 0;
	while (tmp[i])
	{
		join = ft_strjoin(tmp[i], "/");
		test = ft_strjoin(join, cmd);
		free(join);
		if (!access(test, F_OK))
		{
			free_tab(tmp);
			return (test);
		}
		free (test);
		i++;
	}
	free_tab(tmp);
	return (NULL);
}
//lst functions
t_cmds	*ft_new_node(char *str, char *path)
{
	t_cmds *new;

	new = (t_cmds *)malloc(sizeof(t_all));
	if (!new)
		return (NULL);
	new->cmd = ft_split(str, ' ');
	new->path = ft_get_path(new->cmd[0], path);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	if(!new)
		return ;
	if (!lst[0])
	{
		lst[0] = new;
		return ;
	}
	tmp = lst[0];
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_list(t_cmds *lst)
{
	while (lst)
	{
		if (lst->cmd)
			free_tab(lst->cmd);
		if (lst->path)
			free(lst->path);
		if (lst)
			free(lst);
		lst = lst->next;
	}
}

void	ft_fill_lst(t_cmds **lst, char **av, int ac, char *path)
{
	t_cmds *tmp;
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
			exit(0) ;
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

void	ft_exec(t_all all, char **env)
{
	int f1;
	int f2;

	f1 = fork();
	if (f1 < 0)
		ft_error(NULL);
	if (!f1)
	{
		dup2(all.p[1], STDOUT_FILENO);
		dup2(all.fd[0], STDIN_FILENO);
		close(all.p[0]);
		close(all.p[1]);
		execve(all.head->path, all.head->cmd, env);
	}
	f2 = fork();
	if (f2 < 0)
		ft_error(NULL);
	if (!f2)
	{
		dup2(all.p[0], STDIN_FILENO);
		dup2(all.fd[1], STDOUT_FILENO);
		close(all.p[0]);
		close(all.p[1]);
		execve(all.head->next->path, all.head->next->cmd, env);
	}
	waitpid(f1, NULL, 0);
	exit(0);
}

int main(int ac, char *av[], char *env[])
{
	t_all	all;

	if (ac != 5)
		ft_error("Error : wrong number of arguments");
	ft_parse_args(&all, av, ac - 1, env);
	ft_exec(all, env);
	t_cmds *tmp = all.head;
	while(tmp)
	{
		printf("%s\n",tmp->cmd[0]);
		printf("%s\n",tmp->path);
		printf("------------------------\n");
		tmp = tmp->next;
	}
	free_list(all.head);
	return 0;
}
