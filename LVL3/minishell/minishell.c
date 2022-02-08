/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:18:14 by hdrabi            #+#    #+#             */
/*   Updated: 2022/02/08 16:25:10 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define TABLE "|&<>"
#define PIPE 0
#define S_QUOTE 1
#define D_QUOTE 2
#define OR 3
#define INPUT 4
#define OUTPUT 5
#define H_DOC 6
#define A_OUTPUT 7
#define DOLLAR 8
#define AND 9
#define INFILE 10
#define OUTFIL 11
#define C_FILE 'f'
#define C_OPTION 'o'
#define C_CMD 'c'

/* ************************************************************************** */
typedef struct s_tree
{
	char	type;
	int		token;
	char	**cmd;
	char	*path;
	int		fd;
	struct s_tree *parent;
	struct s_tree *left;
	struct s_tree *right;
} t_tree;

typedef struct s_all
{
	struct s_tree *root;

} t_all;

/* ************************************************************************** */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr(char *s, int c)
{
	int	i;
	char get;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			get = s[i++];
			while (s[i] != get)
				i++;
		}
		if (s[i] == (char)c)
		{
			if (s[i + 1] == (char)c)
				break ;
			return (i);
		}
		i++;
	}
	return (-1);
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
/* ************************************************************************** */

void ft_find_error(char *str)
{
	int i;
	char get;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] =='\'')
		{
			get = str[i++];
			while (str[i] && str[i] != get)
				i++;
			if (!str[i])
			{
				printf("ERROR!!!\n");
				break ;
			}
		}
		if (ft_strchr(TABLE, str[i]) != -1 && str[i + 1] == ' ')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (ft_strchr(TABLE, str[i]) != -1)
			{
				printf("ERROR!!!\n");
				break;
			}
		}
		i++;
	}
}
/* ************************************************************************** */
t_tree	*ft_new_node(char t, int tok, t_tree *parent)
{
	t_tree *new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->type = t;
	new->token = tok;
	new->parent = parent;
	new->left = NULL;
	new->right = NULL;
	return (new);
}
void	ft_fill_tree (char *str, t_tree **node, t_tree *parent)
{
	int i;

	i = ft_strchr(str, '|');
	if (i != -1)
	{
		node[0] = ft_new_node(C_OPTION, PIPE, parent);
		ft_fill_tree(ft_substr(str, 0, i - 1), &node[0]->left, node[0]);
		ft_fill_tree(ft_substr(str, i + 1, ft_strlen(str)),&node[0]->right, node[0]);
	}

	else
	{
		node[0] = ft_new_node(C_CMD, INFILE, parent);
		return ;
	}
}
void	ft_create_tree(char *str, t_all *all)
{
	t_tree *root;

	root = NULL;
	ft_fill_tree(str, &root, NULL);
}
/* ************************************************************************** */

/* ************************************************************************** */

/* ************************************************************************** */
int main()
{
	char *str;
	t_all all;

	while (1)
	{
		str = readline("Minishell > ");
		ft_find_error(str);
		ft_create_tree(str, &all);
	}
	return (0);
}
