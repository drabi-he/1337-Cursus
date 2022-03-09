/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 13:15:22 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/09 17:56:07 by hdrabi           ###   ########.fr       */
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
	t_garbage	*head;
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

	pid == fork();
	if (pid == -1)
		ft_panic("ERROR: fork failed!\n");
	return (pid);
}

/* **************************** CONSTRUCTORS **************************** */
t_cmd	*ft_exec_cmd(t_garbage *head)
{
	t_exec	*cmd;

	cmd = ft_malloc(sizeof(t_exec), &head);
	if (!cmd)
		return (NULL);
	cmd->type = EXEC;
	return ((t_cmd *) cmd);
}

t_cmd	*ft_redir_cmd(t_garbage *head, t_cmd *subcmd, char *file, int mode)
{
	t_red	*cmd;

	cmd = ft_malloc(sizeof(t_red), &head);
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

t_cmd	*ft_pipe_cmd(t_garbage *head, t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = ft_malloc(sizeof(t_pipe), &head);
	if (!cmd)
		return (NULL);
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *) cmd);
}

t_cmd	*ft_operator_cmd(t_garbage *head, t_cmd *left, t_cmd *right, int type)
{
	t_operator	*cmd;

	cmd = ft_malloc(sizeof(t_operator), &head);
	if (!cmd)
		return (NULL);
	cmd->type = type;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *) cmd);
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
/* **************************** LIBRARIES **************************** */
/* **************************** LIBRARIES **************************** */
/* ******************************************************************* */

int main(int ac, char *av[], char *env[])
{
	t_all all;
	char *str;

	while(1)
	{
		str = readline("\033[0;33m\e[1mMiniShell--> \e[0m\033[0m");
		free(str);
	}
}
