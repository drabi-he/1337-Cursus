/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:18:59 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/09 11:41:44 by hdrabi           ###   ########.fr       */
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
	int			status;
	int			p[2];
	int			last_fd;
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
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
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

	if (!s1)
		return (NULL);
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

char	*ft_strdup_malloc(char *s1, t_garbage *head)
{
	char	*copy;
	int		i;

	if (!s1)
		return (NULL);
	copy = (char *)ft_malloc(sizeof(char) * (ft_strlen(s1) + 1), &head);
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
	if (!len && ft_strlen(s1) != 1)
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
    if (!s1 && !s2)
        return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
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

char *ft_get_env(t_env *head, char *search)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, search))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
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

/* **************************** STANDAR SPLIT **************************** */
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
					printf("i = %d\n", i + 2);
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
	if(!access(".tmp", F_OK))
		unlink(".tmp");
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
		if (node->token == H_DOC)
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
		if (root->token == DELIMITER)
			root->fd = open(".tmp", O_WRONLY | O_CREAT , 0644);
	}
	if (root->fd == -1)
		return (1);
	ft_check_tree2(root->right);
	ft_check_tree2(root->left);
	return (0);
}

int	ft_is_builtin(t_tree *node, char *str)
{
	if (!ft_strcmp("echo", str) || !ft_strcmp("pwd", str) || !ft_strcmp("cd", str)\
		|| !ft_strcmp("unset", str) || !ft_strcmp("export", str) || !ft_strcmp("env", str)\
		|| !ft_strcmp("exit", str))
	{
		node->is_builtin = 1;
		return (1);
	}
	else
	{
		node->is_builtin = 0;
		return (0);
	}
}

int	ft_get_path(t_tree *node, char **path, t_garbage *head)
{
	int		i;
	char *test1;
	char *test2;

	if (!path)
		return (1);
	i = ft_strchr(node->cmd[0], '/');
	if (i != -1)
	{
		if (access(node->cmd[0], F_OK))
			return (1);
		else
			node->path = ft_strdup_malloc(node->cmd[0], head);
		return (0);
	}
	else
	{
		i = 0;
		if(ft_is_builtin(node, node->cmd[0]))
			return (0);
		while (path[i])
		{
			test1 = ft_strjoin(path[i], "/");
			test2 = ft_strjoin(test1, node->cmd[0]);
			free(test1);
			if (!access(test2, F_OK))
			{
				node->path = ft_strdup_malloc(test2, head);
				free(test2);
				return (0);
			}
			i++;
		}
	}
	return (1);
}

int	ft_check_tree3(t_tree *root, char **path, t_garbage *head)
{
	if (!root)
		return (0);
	if (root->token == COMMAND)
	{
		if(ft_get_path(root, path, head))
		{
			printf("11 - MiniShell: %s: No such file or directory\n", root->cmd[0]);
			return (1);
		}
	}
	ft_check_tree3(root->right, path, head);
	ft_check_tree3(root->left, path, head);
	return (0);
}


// void	ft_exec_cmd1(t_all *all, t_tree *root, int i)
// {

// 	dup2(all->last_fd, 0);
// 	if (root->parent && root->parent->right && root->parent->right != root)
// 		dup2(all->p[1], 1);
// 	close(all->p[0]);
// 	execve(root->path,root->cmd, NULL);
// }

// void	ft_exec_cmd1(t_all *all, t_tree *root, int i)
// {
// 	execve(root->path,root->cmd, NULL);
// }

// void	ft_exec_pipe(t_all *all, t_tree *root)
// {

// }

// void	ft_exec_and(t_all *all, t_tree *root)
// {

// }

void	ft_exec(t_all *all, t_tree *root)
{
	pid_t	pid;

	if (!root)
		return ;
	pipe(all->p);
	pid = fork();
	if (pid < 0)
	{
		printf("11 - failed to fork\n");
		return ;
	}
	if (pid == 0)
	{
		if (root->token == COMMAND && root->is_builtin != 1)
		{
			dup2(all->last_fd, 0);
			if (root->parent && root->parent->right && root->parent->right != root)
				dup2(all->p[1], 1);
			close(all->p[0]);
			execve(root->path,root->cmd, NULL);
		}
		else if (root->token == PIPE)
		{
			ft_exec(all, root->left);
			ft_exec(all, root->right);
			wait(NULL);
		}
		else if (root->token == AND)
		{
			ft_exec(all, root->left);
			wait(NULL);
			if (all->status != 0)
				ft_exec(all, root->right);
		}
			execve(NULL, NULL, NULL);
	}
	// else
	// {
		close(all->p[1]);
		close(all->p[0]);
		all->last_fd = all->p[0];

	// }

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
	char	**paths;

	root = NULL;
	ft_fill_tree(all, &root, str, NULL);
	if(ft_check_tree(root))
		printf("7 - MiniShell: syntax error\n");
	ft_check_tree2(root);
	paths = ft_split(ft_get_env(all->env_head, "PATH"), ':');
	ft_check_tree3(root, paths, all->g_head);
	free_tab(paths);
	all->root = root;
	all->last_fd = 0;
	//ft_print_tree(root, 0, 0);
	ft_exec(all, all->root);
	while(waitpid(-1, &all->status, WUNTRACED) > 0);
}

/* **************************** BUILT-INS **************************** */
void    ft_env(t_env *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		if (lst->value)
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

void	ft_affiche_export(t_env *head)
{
	if (!head)
		return ;
	while (head)
	{
		printf("declare -x ");
		printf("%s", head->key);
		if (head->value)
			printf("=\"%s\"", head->value);
		printf("\n");
		head = head->next;
	}
}

void	ft_export(char *str, t_env *head)
{
	int		i;
	int		cp;
	char	*str1;
	char	*str2;

	if (!str)
	{
		ft_affiche_export(head);
		return ;
	}
	i = -1;
	cp = 0;
	while (str[++i])
	{
		if (ft_isalpha(str[i]))
			cp++;
		if (str[i] > '0' && str[i] < '9' && !cp)
		{
			printf("9 - MiniShell: export: `%s': not a valid identifier\n", str + i);
			return ;
		}
		if (!ft_isalnum(str[i]))
		{
			if (i == 0 || str[i] != '=')
			{
				printf("10 - MiniShell: export: `%s': not a valid identifier\n", str + i);
				return ;
			}
			if (str[i] == '=')
			{
				str1 =ft_substr(str, 0, i);
				str2 =ft_substr(str, i + 1, ft_strlen(str));
				ft_edit_env(head, str1, str2);
				free(str1);
				free(str2);
				return ;
			}
		}
	}
	ft_edit_env(head, str, NULL);
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

/* **************************** HER_DOC **************************** */
char	*ft_parse_dollar(t_env *head, char *str)
{
	int		i;
	int		j;
	char	*rst;

	i = 0;
	j = 0;
	rst = NULL;
	while (str[i])
	{
		if (str[i] == '$' && ft_isalnum(str[i + 1]))
		{
			rst = ft_strjoin(rst, ft_substr(str, j, i - j));
			i++;
			j = i;
			while (str[i] && ft_isalnum(str[i]))
				i++;
			rst = ft_strjoin(rst, ft_get_env(head, ft_substr(str, j, i - j)));
			j = i;
		}
		i++;
	}
	rst = ft_strjoin(rst, ft_substr(str, j, i - j));
	free(str);
	return (rst);
}

void	ft_heredoc(t_env *head, char *limiter, int fd)
{
	char *hdoc;

	while (1)
	{
		if (!ft_strcmp(limiter, hdoc))
			break;
		hdoc = readline("\033[0;31mheredoc>\033[0m ");
		hdoc = ft_parse_dollar(head, hdoc);
		write (fd, hdoc, ft_strlen(hdoc));
		write (fd, "\n", 1);
		free(hdoc);
	}
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
		if(ft_check_syntax(str) || !ft_strcmp(str, "\0"))
			continue ;
		all.g_head = NULL;
		ft_tree_init(str, &all);
		free(str);
		// int i = 0;
		// while (all.root->cmd && all.root->cmd[i])
		// {
		// 	printf("%s\n",all.root->cmd[i]);
		// 	i++;
		// }
		// ft_export(all.root->cmd[1], all.env_head);
		// ft_env(all.env_head);
		//ft_heredoc(all.env_head, all.root->right->cmd[0],all.root->right->fd);
		ft_close_fd(all.root);
		ft_free_garbage(all.g_head);
	}
	return (0);
}

