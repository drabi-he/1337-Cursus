/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:18:59 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/05 13:21:40 by hdrabi           ###   ########.fr       */
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
#define A_OUTFIL 12
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

typedef struct s_tree
{
	char	type;
	char	token;
	int		is_builtin;
	char	**cmd;
	char	*path;
	int		fd;
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_all
{
	t_garbage	*g_head;
	t_env		*env_head;
	t_tree		*root;
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

int	ft_isalnum(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(char *s1)
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
	}
	return (-1);
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
			printf("1 - MiniShell: syntax error unclosed quote near `%c'\n", str[*i]);
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
			printf("2 - MiniShell: syntax error unclosed quote near `%c'\n", str[*i]);
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

char	*ft_strtrim(char *s1, char *set, t_garbage *head)
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
		rst = (char *)ft_malloc(sizeof(char), &head);
		rst[0] = 0;
		return (rst);
	}
	rst = (char *)ft_malloc((len - i + 2) * sizeof(char), &head);
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

void	ft_recalculate_len(char **str, unsigned int *start, size_t *len, t_garbage *head)
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

char	*ft_substr_malloc(char *s, unsigned int start, size_t len, t_garbage *head)
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
	p = (char *)ft_malloc((len + 1) * sizeof(char), &head);
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

int ft_strstr(char *str, char *to_find, int *n)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		ft_skip_quote(str, &i);
		ft_skip_par(str, &i);
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

char    *ft_strjoin(char *s1, char *s2)
{
    char    *p;
    int        i;
    int        j;

    i = 0;
    j = 0;
    if (!s1 || !s2)
        return (NULL);
    p = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1 * sizeof(char));
    if (!p)
        return (0);
    while (s1[j])
        p[i++] = s1[j++];
    j = 0;
    while (s2[j])
        p[i++] = s2[j++];
    p[i] = 0;
    return (p);
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

void	ft_edit_env(t_env *env, char *key, char *new_val)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_val);
			return ;
		}
		tmp = tmp->next;
	}
	ft_add_env(&env, ft_new_env(ft_strdup(key),ft_strdup(new_val)));
}

/* **************************** SPLIT ECHO **************************** */
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

char	*ft_substr2(char *s, unsigned int start, size_t len, t_garbage *head)
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
	p = (char *)ft_malloc((len + 1) * sizeof(char), &head);
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

void	ft_cpyyy(char *str, char ***t, int j, t_garbage *head)
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
		t[0][j] = ft_substr2(str, len, i - len, head);
		j++;
	}
	t[0][j] = 0;
}

char	**ft_split_echo(char *str, t_garbage *head)
{
	int		i;
	int		j;
	int		len;
	char	get;
	char	**t;


	j = 0;
	ft_count_words(str, &j);
	t = (char **)ft_malloc((j + 1) * sizeof(char *), &head);
	if (!t)
		return (NULL);
	ft_cpyyy(str, &t, 0, head);
	return (t);
}

/* **************************** TREE FUNCTIONS **************************** */
t_tree	*ft_new_node(char type, int token, t_garbage *head, char **cmd)
{
	t_tree	*new;

	new = (t_tree *)ft_malloc(sizeof(t_tree), &head);
	if (!new)
		return (NULL);
	new->type = type;
	new->token = token;
	new->cmd = cmd;
	new->fd = -2;
	new->is_builtin = -1;
	new->path = NULL;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

void	ft_fill_tree(t_all *all, t_tree **node, char *str, t_tree *parent)
{
	int i;
	int n;

	if (!str)
		return ;
	str = ft_strtrim(str, " ", all->g_head);
	i = ft_strchr_v2_0(str);
	n = 0;
	if (i != -1)
	{
		if (str[i] == '|')
			node[0] = ft_new_node(C_OPTION, OR, all->g_head, NULL);
		if (str[i] == '&')
			node[0] = ft_new_node(C_OPTION, AND, all->g_head, NULL);
		if (i != 0)
			ft_fill_tree(all, &node[0]->left, ft_substr_malloc(str, 0, i, all->g_head), node[0]);
		ft_fill_tree(all, &node[0]->right, ft_substr_malloc(str, i + 2, ft_strlen(str), all->g_head), node[0]);
	}
	else
	{
		i = ft_strchr(str, '|');
		if (i != -1)
		{
			node[0] = ft_new_node(C_OPTION, PIPE, all->g_head, NULL);
			if (i != 0)
				ft_fill_tree(all, &node[0]->left, ft_substr_malloc(str, 0, i, all->g_head), node[0]);
			ft_fill_tree(all, &node[0]->right, ft_substr_malloc(str, i + 1, ft_strlen(str), all->g_head), node[0]);
		}
		else
		{
			i = ft_strstr(str, TABLE, &n);
			if (i != -1)
			{
				node[0] = ft_new_node(C_OPTION, get_token(str[i], n), all->g_head, NULL);
				if (n == 0)
				{
					if (i != 0)
						ft_fill_tree(all, &node[0]->left, ft_substr_malloc(str, 0, i, all->g_head), node[0]);
					ft_fill_tree(all, &node[0]->right, ft_substr_malloc(str, i + 1, ft_strlen(str), all->g_head), node[0]);
				}
				else
				{
					if (i != 0)
						ft_fill_tree(all, &node[0]->left, ft_substr_malloc(str, 0, i, all->g_head), node[0]);
					ft_fill_tree(all, &node[0]->right, ft_substr_malloc(str, i + 2, ft_strlen(str), all->g_head), node[0]);
				}
			}
			else
			{
				if (str[0] == 40)
					ft_fill_tree(all, node, ft_substr_malloc(str, 0, ft_strlen(str), all->g_head), NULL);
				else
					node[0] = ft_new_node(C_CMD, COMMAND, all->g_head, ft_split_echo(str, all->g_head));
			}
		}
	}
	node[0]->parent = parent;
}

void	ft_tokening(t_tree *parent, t_tree *node)
{
		if (parent && node->type == C_OPTION && node->left)
	{
		if (parent->token == INPUT)
		{
			node->left->type = C_FILE;
			node->left->token = INFILE;
		}
		if (parent->token == OUTPUT)
		{
			node->left->type = C_FILE;
			node->left->token = OUTFIL;
		}
		if (parent->token == H_DOC)
		{
			node->left->type = C_FILE;
			node->left->token = DELIMITER;
		}
		if (parent->token == A_OUTPUT)
		{
			node->left->type = C_FILE;
			node->left->token = A_OUTFIL;
		}
	}
}

void	ft_close_fd(t_tree *root)
{
	if (!root)
		return ;
	close(root->fd);
	ft_close_fd(root->right);
	ft_close_fd(root->left);
}

void	ft_tokening2(t_tree *node)
{
	if (node && node->type == C_OPTION && node->right && node->right->type == C_CMD)
	{
		if (node->token == INPUT)
		{
			node->right->type = C_FILE;
			node->right->token = INFILE;
		}
		if (node->token == OUTPUT)
		{
			node->right->type = C_FILE;
			node->right->token = OUTFIL;
		}
		if (node->token == DELIMITER)
		{
			node->right->type = C_FILE;
			node->right->token = DELIMITER;
		}
		if (node->token == A_OUTPUT)
		{
			node->right->type = C_FILE;
			node->right->token = A_OUTFIL;
		}
	}
}

int	ft_check_tree(t_tree *root)
{
	if (!root)
		return (0);
	if (root->token == PIPE || root->token == OR || root->token == AND)
	{
		if (!root->right || !root->left)
			return (1);
	}
	if (root->token == INPUT || root->token == OUTPUT || root->token == H_DOC || root->token == A_OUTPUT)
	{
		if (!root->right)
			return (1);
	}
	ft_check_tree(root->right);
	ft_check_tree(root->left);
	ft_tokening(root->parent, root);
	ft_tokening2(root);
	return (0);
}

int	ft_check_tree2(t_tree *root)
{
	if (!root)
		return (0);
	if (root->type == C_FILE)
	{
		if (root->token == INFILE)
		{
			if (access(root->cmd[0], F_OK))
			{
				printf("8 - MiniShell: %s: No such file or directory\n", root->cmd[0]);
				return (1);
			}
			if (access(root->cmd[0], R_OK))
			{
				printf("8 - MiniShell: %s: Permission denied\n", root->cmd[0]);
				return (1);
			}
			root->fd = open(root->cmd[0], O_RDONLY , 0644);
		}
		if (root->token == OUTFIL)
			root->fd = open(root->cmd[0], O_WRONLY | O_CREAT , 0644);
		if (root->token == A_OUTFIL)
			root->fd = open(root->cmd[0], O_WRONLY | O_CREAT | O_APPEND , 0644);
	}
	if (root->fd == -1)
		return (1);
	ft_check_tree2(root->right);
	ft_check_tree2(root->left);
	return (0);
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

void	ft_tree_init(char *str, t_all *all)
{
	t_tree	*root;

	root = NULL;
	ft_fill_tree(all, &root, str, NULL);
	if(ft_check_tree(root))
		printf("7 - MiniShell: syntax error\n");
	ft_check_tree2(root);
	all->root = root;
	ft_print_tree(root, 0, 0);
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

void	ft_pwd()
{
	char path[2000];

	getcwd(path, 2000);
	printf("%s\n", path);
}

void ft_cd(t_env *env, char *s)
{
	char path[2000];

	getcwd(path, 2000);
    if (!s)
        return ;
    if (s[0] != '/' && s[0] != '.')
        ft_strjoin("./", s);
    if (!access(s, F_OK))
	{
		ft_edit_env(env, "OLDPWD", path);
        chdir(s);
		getcwd(path, 2000);
		ft_edit_env(env, "PWD", path);
	}
    else
        printf("%s: not found\n", s);
}

void ft_echo(int index, char **s)
{
    int i;

	i = 0;
	if (!ft_strcmp(s[++index], "-n"))
	{
		i++;
	}
	while (s[++index])
		printf("%s", s[index]);
	if (i)
		printf("\n");
}

void	ft_unset(t_env **lst, char *str, t_garbage *head)
{
	char	*tmp;
	int		i;
	t_env	*tmp_env;
	t_env	*tmp_env2;

	tmp = ft_substr2(str, 0, ft_strlen(str), head);
	i = 0;
	while (tmp[i])
	{
		if(!ft_isalnum(str[i]))
		{
			printf("unset `%s' : not a valid identifier\n", tmp);
			return ;
		}
		i++;
	}
	tmp_env = lst[0];
	while (tmp_env)
	{
		if (tmp_env->next && !ft_strcmp(tmp_env->next->key, tmp))
		{
			tmp_env2 = tmp_env->next;
			tmp_env->next = tmp_env2->next;
			free(tmp_env2->key);
			free(tmp_env2->value);
			free(tmp_env2);
			return ;
		}
		tmp_env = tmp_env->next;
	}
}

void	ft_exit()
{
	printf("exit\n");
	exit(0);
}

/* **************************** ERRORS CHECK **************************** */
int	ft_check_options(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_skip_quote(str, &i) == -1)
			return (1);
		if (ft_strchr(TABLE, str[i]) != -1 && str[i + 1] == ' ')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (ft_strchr(TABLE, str[i]) != -1)
			{
				printf ("2 - MiniShell: syntax error near unexpected token `%c'\n", str[i]);
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_valid_options_mini(char c, char get, int *cp)
{
	if (ft_strchr(TABLE, c) != -1)
	{
		if (get != c)
		{
			printf ("3 - MiniShell: syntax error near unexpected token `%c'\n", c);
			return (1);
		}
		if (get == c)
		{
			(*cp)++;
			if (*cp == 2)
			{
				printf ("3 - MiniShell: syntax error near unexpected token `%c'\n", c);
				return (1);
			}
		}
	}
	if (get == '&' && *cp == 0)
	{
		printf ("4 - MiniShell: syntax error near unexpected token `&'\n");
		return (1);
	}
	return (0);
}

int	ft_valid_options(char *str)
{
	int		i;
	int		cp;
	char	get;

	i = 0;
	cp = 0;
	while (str[i])
	{
		if (ft_skip_quote(str, &i) == -1)
			return (1);
		if (ft_strchr(TABLE, str[i]) != -1)
		{
			get = str[i++];
			if (ft_valid_options_mini(str[i], get, &cp))
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

void	ft_valid_parenthesis_mini(char *str, int *i, int *cp)
{
	while (str[*i] && *cp > 0)
	{
		if (str[*i] == 40)
			(*cp)++;
		if (str[*i] == 41)
			(*cp)--;
		if (*cp)
			(*i)++;
	}
}

int	ft_valid_parenthesis(char *str)
{
	int	i;
	int	cp;

	i = 0;
	cp = 0;
	while (str[i])
	{
		if (ft_skip_quote(str, &i) == -1)
			return (1);
		if (str[i] == 41)
		{
			printf ("5 - MiniShell: syntax error near unexpected token `%c'\n", str[i]);
			return (1);
		}
		if (str[i] == 40)
		{
			cp++;
			i++;
			ft_valid_parenthesis_mini(str, &i, &cp);
		}
		if (cp !=0)
		{
			printf ("6 - MiniShell: syntax error near unexpected token `%c'\n", str[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_check_syntax(char *str)
{
	if(ft_check_options(str))
	{
		free(str);
		return (1);
	}
	if(ft_valid_options(str))
	{
		free(str);
		return (1);
	}
	if(ft_valid_parenthesis(str))
	{
		free(str);
		return (1);
	}
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
		all.g_head = NULL;
		ft_tree_init(str, &all);
		free(str);
		ft_close_fd(all.root);
		ft_free_garbage(all.g_head);
	}
	return (0);
}

