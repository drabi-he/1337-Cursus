/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:18:59 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/01 13:55:28 by hdrabi           ###   ########.fr       */
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
#define TABLE "|&<>"
#define PIPE 0
#define OR 1
#define AND 2
#define INPUT 3
#define OUTPUT 4
#define H_DOC 5
#define A_OUTPUT 6
#define DOLLAR 7
#define INFILE 8
#define OUTFIL 9
#define DELIMITER 10
#define COMMAND 11
#define C_FILE 'f'
#define C_OPTION 'o'
#define C_CMD 'c'

#define COUNT 20
/* **************************** STRUCTS **************************** */
typedef struct s_garbage
{
	void				**addr;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_all
{
	t_garbage	*g_head;
	t_env		*env_head;
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
/* **************************** ENV FUNCTIONS **************************** */
t_env	*ft_new_env(char *key, char *value)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_add_env(t_env **lst, t_env *new)
{
	t_env *tmp;

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

int	ft_env_split(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_free_env(t_env *env)
{
	while (env)
	{
		free(env->key);
		if (env->value)
			free(env->value);
		free (env);
		env = env->next;
	}
}
/* **************************** UTILS FUNCTIONS **************************** */
size_t	ft_strlen(const char *s)
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

char	*ft_substr(char *s, unsigned int start, size_t len)
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

/* **************************** INIT FUNCTIONS **************************** */
void	ft_env_init(t_env **env, char *e[])
{
	int	i;
	int j;

	i = 0;
	env[0] = NULL;
	if (!e[0])
	{
		printf("ERROR : cannot work without env\n");
		exit(EXIT_FAILURE);
	}
	while (e[i])
	{
		j = ft_env_split(e[i]);
		ft_add_env(env, ft_new_env(ft_substr(e[i], 0, j), ft_substr(e[i], j + 1, ft_strlen(e[i]))));
		i++;
	}
}

/* **************************** BUILT-INS **************************** */
void    ft_env(t_env *lst)
{
    if (!lst)
        return ;
    while (lst)
    {
        printf("%s=%s\n", lst->key, lst->value);
        lst = lst->next;
    }
}

/* **************************** ERRORS CHECK **************************** */

int	ft_check_syntax(char *str)
{

	return (0);
}
/* **************************** main **************************** */
int main(int ac, char *av[], char *env[])
{
	t_all	all;
	char	*str;

	ft_env_init(&all.env_head, env);
	while (1)
	{
		str = readline("\033[0;36m\e[1mMiniShell > \e[0m\033[0m");
		add_history(str);
		if(ft_check_syntax(str))
			continue ;
		free(str);
	}
	return (0);
}
