/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:18:14 by hdrabi            #+#    #+#             */
/*   Updated: 2022/02/12 16:34:48 by hdrabi           ###   ########.fr       */
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
#define P_OPEN 1
#define P_CLOSE 2
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
/* ************************************************************************** */

/*--------------------------env fill-------------------*/
typedef struct s_env
{
	char *name;
	char *val;
	struct s_env *next;
} t_env;

/* ************************************************************************** */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
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

/* ************************************************************************** */
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

char	*ft_substr2(char *s, unsigned int start, size_t len)
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
	p = (char *)malloc((len + 1) * sizeof(char));
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

void	ft_count_words(char *str, int *j)
{
	int		i;
	int		k;
	char	get;

	i = -1;
	while (str[++i])
	{
		k = 0;
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				get = str[i++];
				while (str[i] && str[i] != get)
					i++;
			}
			k++;
			i++;
		}
		if (k)
			(*j)++;
	}
}

void	ft_cpyyy(char *str, char ***t, int j)
{
	int		i;
	int		len;
	char	get;

	i = -1;
	while (str[++i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		len = i;
		while (str[i] && str[i] != ' ')
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				get = str[i++];
				while (str[i] && str[i] != get)
					i++;
			}
			i++;
		}
		t[0][j] = ft_substr2(str, len, i - len);
		j++;
	}
	t[0][j] = 0;
}

char	**ft_split_echo(char *str)
{
	int		i;
	int		j;
	int		len;
	char	get;
	char	**t;


	j = 0;
	ft_count_words(str, &j);
	t = malloc((j + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	ft_cpyyy(str, &t, 0);
	return (t);
}
/* ************************************************************************** */

t_env	*ft_new_node_env(char **env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = env[0];
	new->val = env[1];
	new->next = NULL;
	return (new);
}

t_env	*ft_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!lst[0])
	{
		lst[0] = new;
		return ;
	}
	tmp = ft_lstlast(lst[0]);
	tmp->next = new;
}

void fill_list(char **env, t_env **env_list)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_lstadd_back(env_list, ft_new_node_env(ft_split(env[i], '=')));
		i++;
	}
}

void	ft_affiche(t_env *lst)
{
	//return ;
	if (!lst)
		return ;
	while (lst)
	{
		printf("%s=%s\n", lst->name, lst->val);
		lst = lst->next;
	}
}

/* ************************************************************************** */

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
    printf("p %d | t %d | %c | %s | %d \n", pos, root->token, root->type, root->cmd? root->cmd[0] : "null", root->fd);

    // Process left child
    ft_print_tree(root->left, space, pos +1);
}

void ft_tokening(t_tree *parent, t_tree *node)
{
	if (parent && node->type == 'o' && node->left)
	{
		if (parent->token == 4)
		{
			node->left->type = C_FILE;
			node->left->token = INFILE;
		}
		if (parent->token == 5)
		{
			node->left->type = C_FILE;
			node->left->token = OUTFIL;
		}
		if (parent->token == 6)
		{
			node->left->type = C_FILE;
			node->left->token = DELIMITER;
		}
		if (parent->token == 7)
		{
			node->left->type = C_FILE;
			node->left->token = A_OUTPUT;
		}
	}
}

void ft_tokening2(t_tree *node)
{
	if (node && node->type == 'o' && node->right && node->right->type == C_CMD)
	{
		if (node->token == 4)
		{
			node->right->type = C_FILE;
			node->right->token = INFILE;
		}
		if (node->token == 5)
		{
			node->right->type = C_FILE;
			node->right->token = OUTFIL;
		}
		if (node->token == 6)
		{
			node->right->type = C_FILE;
			node->right->token = DELIMITER;
		}
		if (node->token == 7)
		{
			node->right->type = C_FILE;
			node->right->token = A_OUTPUT;
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
		{
			printf("1 syntax error!!\n");
			return ;
		}
	}
	if (root->token == 4 || root->token == 5 || root->token == 6 || root->token == 7)
	{
		if (!root->right)
		{
			printf("2 syntax error!!\n");
			return ;
		}
	}
	ft_check_tree(root->right);
    ft_check_tree(root->left);
	ft_tokening(root->parent, root);
	ft_tokening2(root);
}

void ft_check_tree2(t_tree *root)
{
	if (root == NULL)
        return ;
	if (root->type == 'f')
	{
		if (root->token == 7)
			root->fd = open(root->cmd[0], O_WRONLY | O_CREAT | O_APPEND , 0644);
		if (root->token == 10)
		{
			if (access(root->cmd[0], F_OK | R_OK))
				printf("FILE %s not found or permission denied!!\n", root->cmd[0]);
			else
				root->fd = open(root->cmd[0], O_RDONLY , 0644);
		}
		if (root->token == 11)
			root->fd = open(root->cmd[0], O_WRONLY | O_CREAT , 0644);
	}
	ft_check_tree2(root->right);
    ft_check_tree2(root->left);
}

/* ************************************************************************** */
int	ft_get_index(char const *str, char const *set, int cp, int index)
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

char	*ft_strtrim(char *s1, char *set)
{
	char	*rst;
	int		i;
	int		len;
	int		j;

	if (!s1)
		return (NULL);
	i = ft_get_index(s1, set, 1, 0);
	len = ft_get_index(s1, set, -1, ft_strlen(s1) - 1);
	if (!len)
	{
		rst = (char *)malloc(sizeof(char));
		rst[0] = 0;
		return (rst);
	}
	rst = (char *)malloc((len - i + 2) * sizeof(char));
	if (!rst)
		return (NULL);
	j = 0;
	while (i <= len)
		rst[j++] = s1[i++];
	rst[j] = 0;
	return (rst);
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

	s = ft_strtrim(s, " ");
	if (!s || start < 0)
		return (NULL);
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	if (ft_strlen(s) <= start)
		return (NULL);
	if (s[0] == 40)
	{
		len -= 2;
		start++;
	}
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
	int cp;

	i = 0;
	cp = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			get = str[i++];
			while (str[i] != get)
				i++;
		}
		if (str[i] == 40)
		{
			cp++;
			i++;
			while (str[i] && cp > 0)
			{
				if (str[i] == 41)
					cp--;
				if (str[i] == 40)
					cp++;
				i++;
			}
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
int ft_find_error(char *str)
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
				return (1);
		}
		if (ft_strchr(TABLE, str[i]) != -1 && str[i + 1] == ' ')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (ft_strchr(TABLE, str[i]) != -1)
				return (1);
		}
		i++;
	}
	return (0);
}

int ft_find_error2(char *str)
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
				return (1);
		}
		if (ft_strchr(TABLE, str[i]) != -1)
		{
			get = str[i++];
			while (str[i] == ' ')
				i++;
			if (ft_strchr(TABLE, str[i]) != -1)
			{
				if (get != str[i])
					return (1);
				if (get == str[i])
				{
					cp++;
					if (cp == 2)
						return (1);
				}
			}
			if (get == '&' && cp == 0)
				return (1);
		}
		else
		{
			cp = 0;
			i++;
		}
	}
	return (0);
}

int ft_find_error3(char *str)
{
	int i;
	int cp;
	char get;

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
				return (1);
		}
		if (str[i] == 41)
			return (1);
		if (str[i] == 40)
		{
			cp++;
			i++;
			while (str[i] && cp > 0)
			{
				if (str[i] == 40)
					cp++;
				if (str[i] == 41)
					cp--;
				if (cp)
					i++;
			}
		}
		if (cp !=0)
			return (1);
		i++;
	}
	return (0);
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

t_tree	*ft_new_node(char t, int tok, t_tree *parent, char **cmd)
{
	t_tree *new;

	new = malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->type = t;
	new->token = tok;
	new->parent = parent;
	new->cmd = cmd;
	new->fd = -2;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	ft_fill_tree (char *str, t_tree **node, t_tree *parent)
{
	int i;
	int j;
	int n;

	if (!str)
		return ;
	i = ft_strchr(ft_strtrim(str, " "), '|');
	n = 0;
	if (i != -1)
	{
		node[0] = ft_new_node(C_OPTION, PIPE, parent, NULL);
		if (i != 0)
			ft_fill_tree(ft_substr(str, 0, i), &node[0]->left, node[0]);
		ft_fill_tree(ft_substr(str, i + 1, ft_strlen(str)),&node[0]->right, node[0]);
	}
	else if (ft_strstr(str, TABLE, &n) != -1)
	{
		j = ft_strstr(ft_strtrim(str, " "), TABLE, &n);
		node[0] = ft_new_node(C_OPTION, get_token(str[j], n), parent, NULL);
		if (n == 0)
		{
			if (j != 0)
				ft_fill_tree(ft_substr(str, 0, j), &node[0]->left, node[0]);
			ft_fill_tree(ft_substr(str, j + 1, ft_strlen(str)),&node[0]->right, node[0]);
		}
		else
		{
			if (j != 0)
				ft_fill_tree(ft_substr(str, 0, j), &node[0]->left, node[0]);
			ft_fill_tree(ft_substr(str, j + 2, ft_strlen(str)),&node[0]->right, node[0]);
		}
	}
	else
	{
		if (ft_strtrim(str, " ")[0] == 40)
			ft_fill_tree(ft_substr(str, 0, ft_strlen(str)),node,NULL);
		else
			node[0] = ft_new_node(C_CMD, COMMAND, parent, ft_split_echo(str));
		return ;
	}
}

void	ft_create_tree(char *str, t_all *all)
{
	t_tree *root;

	root = NULL;
	ft_fill_tree(str, &root, NULL);

	ft_check_tree(root);
	ft_check_tree2(root);
	ft_print_tree(root, 0, 0);
	// int i = 0;
	// while (root->cmd[i])
	// 	printf("%s\n", root->cmd[i++]);
}

/* ************************************************************************** */

/* ************************************************************************** */

/* ************************************************************************** */
int main(int ac, char *av[], char *env[])
{
	char *str;
	t_all all;
	t_env *lst;
	char **test;

	if (!env[0])
	{
		printf("env -i dirha lmok machi lina \n");
		exit(0);
	}
	fill_list(env, &lst);
	//cuhft_affiche(lst);
	while (1)
	{
		str = readline("\033[0;36m\e[1mMinishell > \e[0m\033[0m");
		add_history(str);
		if (ft_find_error(str) || ft_find_error2(str) || ft_find_error3(str))
		{
			printf("syntax error!!\n");
			free(str);
			continue ;
		}
		ft_create_tree(str, &all);
		// int i = 0;
		// test = ft_split_echo(str);
		// while (test[i])
		// 	printf("%s\n", test[i++]);
		free(str);
	}
	return (0);
}
