/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:18:14 by hdrabi            #+#    #+#             */
/*   Updated: 2022/02/09 15:55:38 by hdrabi           ###   ########.fr       */
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
#define COMMAND 12
#define DELIMITER 13
#define C_FILE 'f'
#define C_OPTION 'o'
#define C_CMD 'c'

#define COUNT 20
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

void ft_print_tree(t_tree *root, int space, int pos)
{
	if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    ft_print_tree(root->right, space, pos + 1);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("p %d = t %d\n", pos, root->token);

    // Process left child
    ft_print_tree(root->left, space, pos +1);
}

void ft_tokening(t_tree *parent, t_tree *node)
{
	if (parent)
	{
		if (parent->token == 4)
		{
			node->type = C_FILE;
			node->token = INFILE;
		}
		if (parent->token == 5)
		{
			node->type = C_FILE;
			node->token = OUTFIL;
		}
		if (parent->token == 6)
		{
			node->type = C_FILE;
			node->token = DELIMITER;
		}
		if (parent->token == 7)
		{
			node->type = C_FILE;
			node->token = A_OUTPUT;
		}
	}
}
void ft_check_tree(t_tree *root)
{
	if (root == NULL)
        return ;
	if (root->token == 0 || root->token == 3 || root->token == 9)
	{
		if (!root->left || !root->right)
			printf("4 syntax error!!\n");
		return ;
	}
	if (root->token == 4 || root->token == 5 || root->token == 6 || root->token == 7)
	{
		if (!root->right)
			printf("5 syntax error!!\n");
		return ;
	}
	ft_tokening(root->parent, root);
    ft_check_tree(root->right);
    ft_check_tree(root->left);
}
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

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*p;

	if (!s || start < 0)
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

int ft_strstr(char *str, char *to_find, int *n)
{
	int	i;
	int	j;
	char get;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			get = str[i++];
			while (str[i] != get)
				i++;
		}
		j = 0;
		while (to_find[j])
		{
			if (to_find[j] == str[i])
			{
				if (to_find[j] == str[i + 1])
					*n = 1;
				return (i);
			}
			j++;
		}
		i++;
	}
	return (-1);
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

void ft_find_error2(char *str)
{
	int i;
	char get;
	int cp;
	int nb;

	i = 0;
	cp = 0;
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
		if (ft_strchr(TABLE, str[i]) != -1)
		{
			get = str[i++];
			while (str[i] == ' ')
				i++;
			if (ft_strchr(TABLE, str[i]) != -1)
			{
				if (get != str[i])
				{
					printf("1 syntax error!!\n");
					return ;
				}
				if (get == str[i])
				{
					cp++;
					if (cp == 2)
					{
						printf("2 syntax error!!\n");
						return ;
					}
				}
			}
			if (get == '&' && cp == 0)
			{
				printf("3 syntax error!!\n");
				return ;
			}
		}
		else
		{
			cp = 0;
			i++;
		}
	}
}
/* ************************************************************************** */

int get_token(char c, int n)
{
	if (n == 0)
	{
		if (c == '<')
			return (INPUT);
		if (c == '>')
			return (OUTPUT);
	}
	else
	{
		if (c == '<')
			return (H_DOC);
		if (c == '>')
			return (A_OUTPUT);
		if (c == '|')
			return (OR);
		if (c == '&')
			return (AND);
	}
	return (-1);
}


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
	int j;
	int n;

	i = ft_strchr(str, '|');
	n = 0;
	if (i != -1)
	{
		node[0] = ft_new_node(C_OPTION, PIPE, parent);
		if (i != 0)
			ft_fill_tree(ft_substr(str, 0, i - 1), &node[0]->left, node[0]);
		ft_fill_tree(ft_substr(str, i + 1, ft_strlen(str)),&node[0]->right, node[0]);
	}
	else if (ft_strstr(str, TABLE, &n) != -1)
	{
		j = ft_strstr(str, TABLE, &n);
		node[0] = ft_new_node(C_OPTION, get_token(str[j], n), parent);
		if (n == 0)
		{
			if (j != 0)
				ft_fill_tree(ft_substr(str, 0, j - 1), &node[0]->left, node[0]);
			ft_fill_tree(ft_substr(str, j + 1, ft_strlen(str)),&node[0]->right, node[0]);
		}
		else
		{
			if (j != 0)
				ft_fill_tree(ft_substr(str, 0, j - 1), &node[0]->left, node[0]);
			ft_fill_tree(ft_substr(str, j + 2, ft_strlen(str)),&node[0]->right, node[0]);
		}
	}
	else
	{
		node[0] = ft_new_node(C_CMD, COMMAND, parent);
		return ;
	}
}

void	ft_create_tree(char *str, t_all *all)
{
	t_tree *root;

	root = NULL;
	ft_fill_tree(str, &root, NULL);

	ft_check_tree(root);
	ft_print_tree(root, 0, 0);
	//printf("%d\n", root->token);
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
		add_history(str);
		ft_find_error(str);
		ft_find_error2(str);
		ft_create_tree(str, &all);
	}
	return (0);
}
