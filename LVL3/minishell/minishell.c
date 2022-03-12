/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:15:22 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/12 17:33:52 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* **************************** LIBRARIES **************************** */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <curses.h>
#include <term.h>
#include <readline/readline.h>
#include <readline/history.h>

/* **************************** TOKENS **************************** */
#define PIPE 0
#define OR 1
#define AND 2
#define	REDIRECT 3
#define DOLLAR 4
#define EXEC 5

#define COUNT 10
#define TABLE "|&<>"
/* **************************** STRUCTS **************************** */
typedef struct s_cmd
{
	int	type;
}	t_cmd;


typedef struct s_exec
{
	int		type;
	char	*path;
	char	**cmd;
	char	**args;
}	t_exec;

typedef struct s_red
{
	int		type;
	t_cmd	*cmd;
	char	*filename;
	char	*eof;
	int		mode;
	int		fd;
} t_red;

typedef struct s_pipe
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipe;

typedef	struct s_operator
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_operator;

typedef struct s_garbage
{
	void				**addr;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_all
{
	t_garbage	*g_head;
}	t_all;

/* **************************** GARBAGE FUNCTIONS **************************** */
t_garbage	*ft_new_garbage(void **addr)
{
	t_garbage *new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->addr = addr;
	new->next = NULL;
	return (new);
}

void	ft_add_garbage(t_garbage **lst, t_garbage *new)
{
	t_garbage *tmp;

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

void	ft_free_garbage(t_garbage *garbage)
{
	while (garbage)
	{
		free(garbage->addr);
		free(garbage);
		garbage = garbage->next;
	}
}

/* **************************** UTILS FUNCTIONS **************************** */
size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	**ft_malloc(int alloc, t_garbage **lst)
{
	void	**ptr;

	ptr = (void **)malloc(alloc);
	if (!ptr)
		return (NULL);
	ft_add_garbage(lst, ft_new_garbage(ptr));
	return (ptr);
}

void	ft_panic(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

int		ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		ft_panic("ERROR: fork failed!\n");
	return (pid);
}

void ft_print_tree(t_cmd *root, int space, int pos)
{
	t_exec *exec = NULL;
	t_pipe *pip = NULL;
	t_operator *op = NULL;

	if (root == NULL)
        return;

    space += COUNT;
	if (root->type == PIPE)
		pip = (t_pipe *)root;
	if (root->type == OR || root->type == AND)
		op = (t_operator *)root;
	if (root->type == EXEC)
		exec = (t_exec *)root;

	if (pip)
		ft_print_tree(pip->right, space, pos + 1);
	if (op)
		ft_print_tree(op->right, space, pos + 1);

	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	if (pip)
		printf("type = %d\n", pip->type);
	if (op)
		printf("type = %d\n", op->type);
	if (exec)
		printf("type = %d\n", exec->type);

	if (pip)
    ft_print_tree(pip->left, space, pos +1);
	if (op)
    ft_print_tree(op->left, space, pos +1);
}

int	ft_skip_quote(char *str, int *i)
{
	char get;

	if (str[*i] == '\"' || str[*i] =='\'')
	{
		get = str[(*i)++];
		while (str[*i] && str[*i] != get)
			(*i)++;
		if (!str[*i])
		{
			printf("MiniShell: syntax error unclosed quote near `%c'\n", str[*i]);
			return (-1);
		}
	}
	return (0);
}

void	ft_skip_par(char *str, int *i)
{
	int cp;

	cp = 0;
	if (str[*i] == 40)
	{
		cp++;
		(*i)++;
		while (str[*i] && cp > 0)
		{
			if (str[*i] == 41)
				cp--;
			if (str[*i] == 40)
				cp++;
			(*i)++;
		}
	}
}

int	ft_skip_quote_rev(char *str, int *i)
{
	char get;

	if (str[*i] == '\"' || str[*i] =='\'')
	{
		get = str[(*i)--];
		while (str[*i] && str[*i] != get)
			(*i)--;
		if (!str[*i])
		{
			printf("MiniShell: syntax error unclosed quote near `%c'\n", str[*i]);
			return (-1);
		}
	}
	return (0);
}

void	ft_skip_par_rev(char *str, int *i)
{
	int cp;

	cp = 0;
	if (str[*i] == 41)
	{
		cp++;
		(*i)--;
		while (str[*i] && cp > 0)
		{
			if (str[*i] == 40)
				cp--;
			if (str[*i] == 41)
				cp++;
			(*i)--;
		}
	}
}

int	ft_strchr(char *s, int c)
{
	int	i;
	char get;

	i = 0;
	while (s[i])
	{
		if (ft_skip_quote(s, &i) == -1)
			return (-1);
		ft_skip_par(s, &i);
		if (s[i] == (char)c)
		{
			if (s[i + 1] == (char)c)
			{
				i += 2;
				continue ;
			}
			return (i);
		}
		i++;
	}
	return (-1);
}

int	ft_get_index(char *str, char *set, int cp, int index)
{
	size_t	j;

	j = 0;
	while (str[index] && set[j])
	{
		if (str[index] == set[j])
		{
			j = 0;
			index += cp;
		}
		else
			j++;
		if (!index)
			break ;
	}
	return (index);
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

char	*ft_strtrim(char *s1, char *set, t_garbage **head)
{
	char	*rst;
	int		i;
	int		len;
	int		j;

	if (!s1)
		return (NULL);
	i = ft_get_index(s1, set, 1, 0);
	len = ft_get_index(s1, set, -1, ft_strlen(s1) - 1);
	if (!len && ft_strlen(s1) != 1)
	{
		rst = (char *)ft_malloc(sizeof(char), head);
		rst[0] = 0;
		return (rst);
	}
	rst = (char *)ft_malloc((len - i + 2) * sizeof(char), head);
	if (!rst)
		return (NULL);
	j = 0;
	while (i <= len)
		rst[j++] = s1[i++];
	rst[j] = 0;
	return (rst);
}

int	ft_strchr_v2_0(char *str)
{
	int i;
	int j;
	int cp;

	i = ft_strrchr(str, '|');
	j = ft_strrchr(str, '&');
	if (i == -1 && j == -1)
		return (-1);
	if (i < j)
		return (j);
	else
		return (i);
}

void	ft_sub_len(char *s, unsigned int start, size_t *len)
{
	char	get;
	int		cp;
	int		i;

	i = 0;
	get = '\0';
	cp = 0;
	if (ft_strlen(s + start) < *len)
		*len = ft_strlen(s + start);
	while (i < *len)
	{
		if ((s[start + i] == '\'' || s[start + i] == '\"') && cp % 2 == 0)
			get = s[start + i];
		if (s[start + i] == get)
			cp++;
		i++;
	}
	*len -= cp;
}

char	*ft_substr2(char *s, unsigned int start, size_t len, t_garbage **head)
{
	size_t	i;
	size_t	j;
	char	*p;
	char	get;
	int		cp;

	if (!s || start < 0)
		return (NULL);
	ft_sub_len(s, start, &len);
	if (ft_strlen(s) <= start)
		return (NULL);
	p = (char *)ft_malloc((len + 1) * sizeof(char), head);
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	cp = 0;
	while (j < len)
	{
		if ((s[start + i] == '\'' || s[start + i] == '\"') && cp % 2 == 0)
			get = s[start + i];
		if (s[start + i] == get)
		{
			cp++;
			i++;
		}
		else
			p[j++] = s[start + i++];
	}
	p[j] = 0;
	return (p);
}

void	ft_recalculate_len(char **str, unsigned int *start, size_t *len, t_garbage **head)
{
	int cp;
	int i;

	i = *start;
	cp = 0;
	str[0] = ft_strtrim(str[0], " ", head);
	(*len)--;
	while (str[0][*len] == ' ')
		(*len)--;
	if (str[0][*len] == 41)
	{
		while (i < *len)
		{
			ft_skip_par(str[0], &i);
			if(ft_strchr(TABLE, str[0][i]) != -1)
			{
				(*len)++;
				return ;
			}
			i++;
		}
		(*len) -= 2;
		(*start)++;
	}
	(*len)++;
}

char	*ft_substr_malloc(char *s, unsigned int start, size_t len, t_garbage **head)
{
	size_t	i;
	char	*p;

	ft_recalculate_len(&s, &start, &len, head);
	if (!s || start < 0)
		return (NULL);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	if (ft_strlen(s) <= start)
		return (NULL);
	p = (char *)ft_malloc((len + 1) * sizeof(char), head);
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

/* **************************** CONSTRUCTORS **************************** */
t_cmd	*ft_exec_cmd(t_garbage **head)
{
	t_exec	*cmd;

	cmd = (t_exec *)ft_malloc(sizeof(t_exec), head);
	if (!cmd)
		return (NULL);
	cmd->type = EXEC;
	return ((t_cmd *) cmd);
}

t_cmd	*ft_redir_cmd(t_garbage **head, t_cmd *subcmd, char *file, int mode)
{
	t_red	*cmd;

	cmd = (t_red *)ft_malloc(sizeof(t_red), head);
	if (!cmd)
		return (NULL);
	cmd->type = REDIRECT;
	cmd->cmd = subcmd;
	cmd->filename = file;
	cmd->eof = NULL; //create a function that gives you the end of the name
	cmd->mode = mode;
	cmd->fd = -2; //create a function that open fd depending on mode
	return ((t_cmd *) cmd);
}

t_cmd	*ft_pipe_cmd(t_garbage **head, t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = (t_pipe *)ft_malloc(sizeof(t_pipe), head);
	if (!cmd)
		return (NULL);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *) cmd);
}

t_cmd	*ft_operator_cmd(t_garbage **head, t_cmd *left, t_cmd *right, int type)
{
	t_operator	*cmd;

	cmd = (t_operator *)ft_malloc(sizeof(t_operator), head);
	if (!cmd)
		return (NULL);
	cmd->type = type;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *) cmd);
}

/* **************************** TREE FUNCTIONS **************************** */
t_cmd	*ft_fill_tree(t_all *all, t_cmd *node, char *str)
{
	int i;
	int n;

	if (!str)
		return (NULL);
	str = ft_strtrim(str, " ", &all->g_head);
	i = ft_strchr_v2_0(str);
	n = 0;
	if (i != -1)
	{
		if (str[i] == '|')
			node = ft_operator_cmd(&all->g_head,\
			ft_fill_tree(all, NULL, ft_substr_malloc(str, 0, i, &all->g_head)),\
			ft_fill_tree(all, NULL, ft_substr_malloc(str, i + 2, ft_strlen(str), &all->g_head)),\
			OR);
		if (str[i] == '&')
			node = ft_operator_cmd(&all->g_head,\
			ft_fill_tree(all, NULL, ft_substr_malloc(str, 0, i, &all->g_head)),\
			ft_fill_tree(all, NULL, ft_substr_malloc(str, i + 2, ft_strlen(str), &all->g_head)),\
			AND);

	}
	else
	{
		i = ft_strchr(str, '|');
		if (i != -1)
		{
			node = ft_pipe_cmd(&all->g_head,\
			ft_fill_tree(all, NULL, ft_substr_malloc(str, 0, i, &all->g_head)),\
			ft_fill_tree(all, NULL, ft_substr_malloc(str, i + 1, ft_strlen(str), &all->g_head)));
		}
		else
		{
			if (str[0] == 40)
			{
				node = ft_exec_cmd(&all->g_head);
				node = ft_fill_tree(all, NULL, ft_substr_malloc(str, 0, ft_strlen(str), &all->g_head));
			}
			else
			{
				t_exec *exe;
				node = ft_exec_cmd(&all->g_head);
			}
		}
	}
	return (node);
}
void ft_exec(t_cmd *cmd);

pid_t	run_pipe(t_pipe *connector, int fds[2], int side)
{
	pid_t		pid;
	int			end;
	int			fileno;
	t_cmd	*cmdtree;

	end = 1;
	fileno = STDOUT_FILENO;
	cmdtree = connector->left;
	if (side & 2)
	{
		end = 0;
		fileno = STDIN_FILENO;
		cmdtree = connector->right;
	}
	pid = ft_fork();
	if (pid == 0)
	{
		dup2(fds[end], fileno);
		close(fds[0]);
		close(fds[1]);
		ft_exec(cmdtree);
		exit(0);
	}
	return (pid);
}

void	run_pipeline(t_pipe *connector)
{
	int	status;
	int	pids[2];
	int	fds[2];

	if (pipe(fds) == -1)
		return ;
	pids[0] = run_pipe(connector, fds, 1);
	if (pids[0] == -1)
		return ;
	pids[1] = run_pipe(connector, fds, 2);
	if (pids[1] == -1)
		return ;
	close(fds[0]);
	close(fds[1]);
	wait(&status);
	wait(&status);
}

void ft_exec(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		char *cmd[] = { "ls", (char *)0};
		execve("/bin/ls", cmd, NULL);
	}
	if (cmd->type == PIPE)
	{
		t_pipe *pip;
		pip = (t_pipe *)cmd;
		run_pipeline(pip);
	}
}

/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* ******************************************************************* */

int main(int ac, char *av[], char *env[])
{
	t_all all;
	t_cmd *cmd;
	char *str;

	while(1)
	{
		str = readline("\033[0;33m\e[1mMiniShell--> \e[0m\033[0m");
		add_history(str);
		cmd = ft_fill_tree(&all, NULL, str);
		//ft_print_tree(cmd, 0, 0);
		ft_exec(cmd);
		free(str);
	}
}
