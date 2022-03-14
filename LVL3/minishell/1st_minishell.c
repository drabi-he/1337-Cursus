/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1st_minishell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 10:18:59 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/14 12:12:35 by momayaz          ###   ########.fr       */
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
#include <dirent.h>
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
	char	*infile;
	char	*outfile;
	int		ifd;
	int		ofd;
	int		p[2];
	int		exist;
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_all
{
	t_garbage	*g_head;
	t_env		*env_head;
	t_tree		*root;
	char		**env;
	int			status;
	int			status_s;
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

void	ft_print_error(char *s1, char *s2, char *s3)
{
	int i;

	i = 0;
	while (s1[i])
	{
		write(2, &s1[i], 1);
		i++;
	}
	i = 0;
	while (s2[i])
	{
		write(2, &s2[i], 1);
		i++;
	}
	i = 0;
	while (s3[i])
	{
		write(2, &s3[i], 1);
		i++;
	}
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
			printf("2 -MiniShell: syntax error unclosed quote near `%c'\n", str[*i]);
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
    printf("p %d | t %d | %c | %s\n", pos, root->token, root->type, root->cmd? root->cmd[0] : "null");

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

char	*ft_strdup_malloc(char *s1, t_garbage **head)
{
	char	*copy;
	int		i;

	if (!s1)
		return (NULL);
	copy = (char *)ft_malloc(sizeof(char) * (ft_strlen(s1) + 1), head);
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
	if (len <= 0)
		return (NULL);
	rst = (char *)ft_malloc((len - i + 2) * sizeof(char), head);
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
	if (str[0][*len] == 41 && str[0][0] == 40)
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

int	ft_alloc(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*rst;
	int				size;
	unsigned int	nb;

	size = ft_alloc(n) + 1;
	rst = (char *)malloc(size * sizeof(char));
	if (!rst)
		return (NULL);
	if (n < 0)
		nb = -n;
	else
		nb = n;
	rst[--size] = 0;
	while (--size >= 0 && nb)
	{
		rst[size] = '0' + nb % 10;
		nb /= 10;
	}
	if (n < 0)
		rst[0] = '-';
	if (n == 0)
		rst[0] = '0';
	return (rst);
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
			return (ft_strdup(tmp->value));
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

void	ft_sub_len2(char *s, unsigned int start, size_t *len)
{
	if (ft_strlen(s + start) < *len)
		*len = ft_strlen(s + start);
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

char	*ft_substr3(char *s, unsigned int start, size_t len, t_garbage **head)
{
	size_t	i;
	size_t	j;
	char	*p;
	char	get;
	int		cp;

	if (!s || start < 0)
		return (NULL);
	ft_sub_len2(s, start, &len);
	if (ft_strlen(s) <= start)
		return (NULL);
	p = (char *)ft_malloc((len + 1) * sizeof(char), head);
	if (!p)
		return (NULL);
	i = 0;
	j = 0;
	cp = 0;
	while (j < len)
		p[j++] = s[start + i++];
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

void	ft_cpyyy(char *str, char ***t, int j, t_garbage **head)
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
		t[0][j] = ft_substr3(str, len, i - len, head);
		j++;
	}
	t[0][j] = 0;
}

char	**ft_split_echo(char *str, t_garbage **head)
{
	int		i;
	int		j;
	int		len;
	char	get;
	char	**t;


	j = 0;
	ft_count_words(str, &j);
	t = (char **)ft_malloc((j + 1) * sizeof(char *), head);
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
	while (t && t[i])
	{
		if (t[i])
			free(t[i]);
		i++;
	}
	if (t)
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

char	**ft_split(char *s, char c)
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

/* **************************** WILDCARD **************************** */
char *str_cpy2(char *s)
{
    size_t len;
    char *t;
    int i;

    len = ft_strlen(s);
    i = 0;
    t = malloc((len + 1) * sizeof(char));
    if (!t)
        return (NULL);
    while (s[i])
    {
        t[i] = s[i];
        i++;
    }
    t[i] = 0;
    return (t);
}

int count_tab_len(void)
{
    DIR *dir;
    struct dirent *wild;
    int i;

    dir = opendir(".");
    i = 0;
    if (dir == NULL)
        return (-1);
    wild = readdir(dir);
    while (wild)
    {
        i++;
        wild = readdir(dir);
    }
    closedir(dir);
    return (i);
}

char **alloc_tab(void)
{
    char **t;
    int i;
    int len;
    DIR *dir;
    struct dirent *wild;

    len = count_tab_len();
    i = 0;
    t = malloc((len + 1) * sizeof(char*));
    if (!t)
        return (NULL);
    dir = opendir(".");
    if (dir == NULL)
        return (NULL);
    wild = readdir(dir);
    while (wild)
    {
		if (!ft_strcmp(wild->d_name, ".") || !ft_strcmp(wild->d_name, ".."))
		{
			wild = readdir(dir);
			continue;
		}
        t[i] = str_cpy2(wild->d_name);
        if (!t[i])
            return (free_tab(t), NULL);
        i++;
        wild = readdir(dir);
    }
    closedir(dir);
	t[i] = 0;
    return (t);
}

char **ft_double_join(char **s1, char **s2, t_garbage **head, int pos)
{
	int i;
	int j;
	int k;

	char **rst;

	while (s1[i])
		i++;
	while (s2[j])
		j++;
	rst =(char **)ft_malloc((i + j) * sizeof(char *), head);
	if (!rst)
		return (NULL);
	i = 0;
	j = 0;
	k = 0;
	while (s1[i])
	{
		if (i != pos)
		{
			rst[k] = ft_strdup_malloc(s1[i], head);
			k++;
		}
		i++;
	}
	while (s2[j])
	{
		rst[k] = ft_strdup_malloc(s2[j], head);
		k++;
		j++;
	}
	rst[k] = 0;
	free_tab(s2);
	return (rst);
}

/* **************************** HER_DOC **************************** */
char    *ft_strjoin2(char *s1, char *s2)
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
	free(s1);
	free(s2);
    return (p);
}

char	*ft_parse_dollar(t_all *all, t_env *head, char *str, int n)
{
	int		i;
	int		j;
	char	*rst;
	char	*tmp;
	i = 0;
	j = 0;
	rst = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			rst = ft_strjoin2(rst, ft_substr(str, j, i - j));
			if (ft_isalnum(str[i + 1]))
			{
				i++;
				j = i;
				while (str[i] && ft_isalnum(str[i]))
					i++;
				tmp = ft_substr(str, j, i - j);
				rst = ft_strjoin2(rst, ft_get_env(head, tmp));
				free (tmp);
				j = i;
			}
			else if (str[i + 1] == '?')
			{
				tmp = ft_itoa(all->status);
				rst = ft_strjoin2(rst, tmp);
				//free(tmp);
				j = i + 2;
			}
		}
		i++;
	}
	rst = ft_strjoin2(rst, ft_substr(str, j, i - j));
	if (n)
		free(str);
	return (rst);
}

void	ft_heredoc(t_all *all, t_env *head, char *limiter, int fd)
{
	char *hdoc;

	while (1)
	{
		all->status_s= 0;
		hdoc = readline("\033[0;31mheredoc>\033[0m ");
		if (!hdoc)
			return ;
		hdoc = ft_parse_dollar(all, head, hdoc, 1);
		if (!ft_strcmp(limiter, hdoc))
			break;
		write (fd, hdoc, ft_strlen(hdoc));
		write (fd, "\n", 1);
		free(hdoc);

	}

}

/* **************************** PARSE CMD **************************** */
void	ft_parse_cmd(t_all *all, char **cmd)
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] != '\'')
		{
			cmd[i] = ft_substr2(cmd[i], 0, ft_strlen(cmd[i]), &all->g_head);
			cmd[i] = ft_parse_dollar(all, all->env_head, cmd[i], 0);
			ft_add_garbage(&all->g_head, ft_new_garbage((void**)cmd[i]));
		}
		else
			cmd[i] = ft_substr2(cmd[i], 0, ft_strlen(cmd[i]), &all->g_head);
		i++;
	}
}

/* **************************** test **************************** */
char	*ft_get_infile(char *str, int i, t_all *all, t_tree **node)
{
	char	*left;
	char	*right;
	char	*rst;
	int	j;

	j = i;
	while (str[j] && str[j] == ' ')
		j++;
	while (str[j] && str[j] != ' ')
		j++;
	node[0]->infile = ft_strtrim(ft_substr2(str, i, j - i, &all->g_head), " ", &all->g_head);
	if (access(node[0]->infile, F_OK | R_OK))
	{
		ft_print_error("MiniShell: ", node[0]->infile, ": file doesn't exist or permission denied!\n");
	}
	node[0]->ifd = open(node[0]->infile, O_RDONLY , 0644);
	left = ft_substr(str, 0, i - 1);
	right = ft_substr(str, j, ft_strlen(str));
	rst = ft_strjoin(left, right);
	return (rst);
}

char	*ft_get_herdoc(char *str, int i, t_all *all, t_tree **node)
{
	char	*left;
	char	*right;
	char	*rst;
	int	j;

	j = i;
	while (str[j] && str[j] == ' ')
		j++;
	while (str[j] && str[j] != ' ')
		j++;
	node[0]->infile = ft_strtrim(ft_substr2(str, i, j - i, &all->g_head), " ", &all->g_head);
	node[0]->ifd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_heredoc(all, all->env_head, node[0]->infile, node[0]->ifd);
	left = ft_substr(str, 0, i - 2);
	right = ft_substr(str, j, ft_strlen(str));
	rst = ft_strjoin(left, right);
	close(node[0]->ifd);
	node[0]->ifd = open(".tmp", O_RDONLY , 0644);
	return (rst);
}

char	*ft_get_outfile(char *str, int i, t_all *all, t_tree **node)
{
	char	*left;
	char	*right;
	char	*rst;
	int	j;

	j = i;
	while (str[j] && str[j] == ' ')
		j++;
	while (str[j] && str[j] != ' ')
		j++;
	node[0]->outfile = ft_strtrim(ft_substr2(str, i, j - i, &all->g_head), " ", &all->g_head);
	if (!access(node[0]->outfile, F_OK) && access(node[0]->outfile, W_OK))
	{
		printf("MiniShell: %s: permission denied!\n", node[0]->outfile);
	}
	node[0]->ofd = open(node[0]->outfile, O_WRONLY | O_CREAT | O_TRUNC , 0644);
	left = ft_substr(str, 0, i - 1);
	right = ft_substr(str, j, ft_strlen(str));
	rst = ft_strjoin(left, right);
	return (rst);
}

char	*ft_get_a_outfile(char *str, int i, t_all *all, t_tree **node)
{
	char	*left;
	char	*right;
	char	*rst;
	int	j;

	j = i;
	while (str[j] && str[j] == ' ')
		j++;
	while (str[j] && str[j] != ' ')
		j++;
	node[0]->outfile = ft_strtrim(ft_substr2(str, i, j - i, &all->g_head), " ", &all->g_head);
	if (!access(node[0]->outfile, F_OK) && access(node[0]->outfile, W_OK))
	{
		printf("MiniShell: %s: permission denied!\n", node[0]->outfile);
	}
	node[0]->ofd = open(node[0]->outfile, O_WRONLY | O_CREAT | O_APPEND , 0644);
	left = ft_substr(str, 0, i - 2);
	right = ft_substr(str, j, ft_strlen(str));
	rst = ft_strjoin(left, right);
	return (rst);
}

void	ft_split_red(char **str, t_all *all, t_tree **node)
{
	int	i;

	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '<')
		{
			i++;
			if (str[0][i] == '<')
			{
				i++;
				str[0] = ft_get_herdoc(str[0], i, all, node);
			}
			else
				str[0] = ft_get_infile(str[0], i, all, node);
			i = 0;
		}
		else if (str[0][i] == '>')
		{
			i++;
			if (str[0][i] == '>')
			{
				i++;
				str[0] = ft_get_a_outfile(str[0], i, all, node);
			}
			else
				str[0] = ft_get_outfile(str[0], i, all, node);
			i = 0;
		}
		else
			i++;
	}
}

/* **************************** TREE FUNCTIONS **************************** */
t_tree	*ft_new_node(char type, int token, t_garbage **head, char **cmd)
{
	t_tree	*new;

	new = (t_tree *)ft_malloc(sizeof(t_tree), head);
	if (!new)
		return (NULL);
	new->type = type;
	new->token = token;
	new->cmd = cmd;
	new->infile = NULL;
	new->outfile = NULL;
	new->ifd = -2;
	new->ofd = -2;
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
	char **tmp;


	if (!str)
		return ;
	str = ft_strtrim(str, " ", &all->g_head);
	i = ft_strchr_v2_0(str);
	n = 0;
	if (i != -1)
	{
		if (str[i] == '|')
			node[0] = ft_new_node(C_OPTION, OR, &all->g_head, NULL);
		if (str[i] == '&')
			node[0] = ft_new_node(C_OPTION, AND, &all->g_head, NULL);
		if (i != 0)
			ft_fill_tree(all, &node[0]->left, ft_substr_malloc(str, 0, i, &all->g_head), node[0]);
		ft_fill_tree(all, &node[0]->right, ft_substr_malloc(str, i + 2, ft_strlen(str), &all->g_head), node[0]);
	}
	else
	{
		i = ft_strchr(str, '|');
		if (i != -1)
		{
			node[0] = ft_new_node(C_OPTION, PIPE, &all->g_head, NULL);
			if (i != 0)
				ft_fill_tree(all, &node[0]->left, ft_substr_malloc(str, 0, i, &all->g_head), node[0]);
			ft_fill_tree(all, &node[0]->right, ft_substr_malloc(str, i + 1, ft_strlen(str), &all->g_head), node[0]);
		}
		else
		{
			if (str[0] == 40)
				ft_fill_tree(all, node, ft_substr_malloc(str, 0, ft_strlen(str), &all->g_head), NULL);
			else
			{
				node[0] = ft_new_node(C_CMD, COMMAND, &all->g_head, NULL);
				ft_split_red(&str, all, node);
				node[0]->cmd = ft_split_echo(str, &all->g_head);
				node[0]->exist = 1;
				i = 0;
				tmp = alloc_tab();
				while (node[0]->cmd[i])
				{
					if (!tmp[0])
						break ;
					if (!ft_strcmp(node[0]->cmd[i], "*"))
					{
						node[0]->cmd = ft_double_join(node[0]->cmd, tmp , &all->g_head,i);
						i = 0;
					}
					i++;
				}
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
	if (root->ifd > 0)
		close(root->ifd);
	if (root->ofd > 0)
		close(root->ofd);
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

int	ft_get_path(t_tree *node, char **path, t_garbage **head)
{
	int		i;
	char	*tmp;
	char *test1;
	char *test2;

	tmp = ft_substr2(node->cmd[0], 0, ft_strlen(node->cmd[0]), head);
	if(ft_is_builtin(node, tmp) == 1)
			return (0);
	if (!path)
		return (1);
	i = ft_strchr(tmp, '/');
	if (i != -1)
	{
		if (access(tmp, F_OK))
			return (1);
		else
			node->path = ft_strdup_malloc(tmp, head);
		return (0);
	}
	else
	{
		i = 0;
		while (path[i])
		{
			test1 = ft_strjoin(path[i], "/");
			test2 = ft_strjoin(test1, tmp);
			free(test1);
			if (!access(test2, F_OK))
			{
				node->path = ft_strdup_malloc(test2, head);
				free(test2);
				return (0);
			}
			free(test2);
			i++;
		}
	}
	return (1);
}

int	ft_check_tree3(t_tree *root, char **path, t_garbage **head)
{
	if (!root)
		return (0);
	if (root->token == COMMAND)
	{
		if(ft_get_path(root, path, head))
		{
			ft_print_error("MiniShell: ", root->cmd[0], ": command not found\n");
			root->exist = 0;
			return (1);
		}
	}
	ft_check_tree3(root->right, path, head);
	ft_check_tree3(root->left, path, head);
	return (0);
}

int	ft_get_list_size(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	ft_list_to_array(t_all *all)
{
	int len;
	int i = 0;
	t_env *tmp;

	len = ft_get_list_size(all->env_head);
	all->env = (char **)malloc((len + 1)* sizeof(char *));
	if (!all->env)
		return ;
	tmp = all->env_head;
	while (tmp)
	{
		all->env[i] = ft_strjoin(ft_strdup(tmp->key), ft_strdup("="));
		all->env[i] = ft_strjoin(ft_strdup(all->env[i]), ft_strdup(tmp->value));
		i++;
		tmp = tmp->next;
	}
}

/* **************************** BUILT-INS **************************** */
int	ft_env(t_env *lst)
{
	if (!lst)
		return (1);
	while (lst)
	{
		if (lst->value)
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return (0);
}

int	ft_pwd()
{
	char path[2000];

	getcwd(path, 2000);
	printf("%s\n", path);
	return (0);
}

int ft_cd(t_env *env, char *s)
{
	char path[2000];
	char *home;

	getcwd(path, 2000);
    if (!s)
	{
		home = ft_get_env(env, "HOME");
		if (!home)
		{
			write(2, "MiniShell: cd: HOME not set\n", 28);
			return (1);
		}
		ft_edit_env(env, "OLDPWD", path);
        chdir(home);
		getcwd(path, 2000);
		ft_edit_env(env, "PWD", path);
		return (0);
	}
    if (s[0] != '/' && s[0] != '.')
        ft_strjoin("./", s);
    if (!access(s, F_OK))
	{
		ft_edit_env(env, "OLDPWD", path);
        chdir(s);
		getcwd(path, 2000);
		ft_edit_env(env, "PWD", path);
		return (0);
	}
    else
	{
        printf("%s: not found\n", s);
		return (1);
	}
}

int ft_echo(int index, char **s)
{
    int i;

	i = 0;
	while (s[index] && !ft_strcmp(s[index], "-n"))
	{
		index++;
		i++;
	}
	while (s[index])
	{
		printf("%s", s[index++]);
		if (s[index])
			printf(" ");
	}
	if (!i)
		printf("\n");
	return (0);
}

int	ft_unset(t_env **lst, char *str)
{
	int		i;
	t_env	*tmp_env;
	t_env	*tmp_env2;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if(!ft_isalnum(str[i]))
		{
			printf("unset `%s' : not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	tmp_env = lst[0];
	while (tmp_env)
	{
		if (tmp_env->next && !ft_strcmp(tmp_env->next->key, str))
		{
			tmp_env2 = tmp_env->next;
			tmp_env->next = tmp_env2->next;
			free(tmp_env2->key);
			free(tmp_env2->value);
			free(tmp_env2);
			return (0);
		}
		tmp_env = tmp_env->next;
	}
	return (1);
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

int	ft_export(char *str, t_env *head)
{
	int		i;
	int		cp;
	char	*str1;
	char	*str2;

	if (!str)
	{
		ft_affiche_export(head);
		return (0);
	}
	i = -1;
	cp = 0;
	while (str[++i])
	{
		if (ft_isalpha(str[i]))
			cp++;
		if (str[i] > '0' && str[i] < '9' && !cp)
		{
			ft_print_error("9 - MiniShell: export: `", str + i,"': not a valid identifier\n");
			return (1);
		}
		if (!ft_isalnum(str[i]))
		{
			if (i == 0 || str[i] != '=')
			{
				ft_print_error("MiniShell: export: `", str + i, "': not a valid identifier\n");
				return (1);
			}
			if (str[i] == '=')
			{
				str1 =ft_substr(str, 0, i);
				str2 =ft_substr(str, i + 1, ft_strlen(str));
				ft_edit_env(head, str1, str2);
				free(str1);
				free(str2);
				return (0);
			}
		}
	}
	ft_edit_env(head, str, NULL);
	return (0);
}

void	ft_exit()
{
	printf("exit\n");
	exit(0);
}

/* **************************** EXEC FUNCTIONS **************************** */
void ft_exec_builtin(t_all *all, t_tree *root)
{
	if (!ft_strcmp(root->cmd[0], "cd"))
		all->status = ft_cd(all->env_head, root->cmd[1]);
	if (!ft_strcmp(root->cmd[0], "pwd"))
		all->status = ft_pwd();
	if (!ft_strcmp(root->cmd[0], "env"))
		all->status = ft_env(all->env_head);
	if (!ft_strcmp(root->cmd[0], "echo"))
		all->status = ft_echo(1, root->cmd);
	if (!ft_strcmp(root->cmd[0], "unset"))
		all->status = ft_unset(&all->env_head, root->cmd[1]);
	if (!ft_strcmp(root->cmd[0], "export"))
		all->status = ft_export(root->cmd[1], all->env_head);
	if (!ft_strcmp(root->cmd[0], "exit"))
	{
		all->status = 0;
		ft_exit();
	}
	if (root->parent && root->parent->token == PIPE)
		exit(0);
}

void	ft_exec(t_all *all, t_tree *root, int n);

pid_t	run_pipe(t_all *all, t_tree *root, int fds[2], int side)
{
	pid_t		pid;
	int			end;
	int			fileno;
	t_tree	*cmdtree;

	end = 1;
	fileno = STDOUT_FILENO;
	cmdtree = root->left;
	if (side & 2)
	{
		end = 0;
		fileno = STDIN_FILENO;
		cmdtree = root->right;
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fds[end], fileno);
		close(fds[0]);
		close(fds[1]);
		ft_exec(all, cmdtree, 1);
		exit(0);
	}
	return (pid);
}

void	run_pipeline(t_all *all, t_tree *root)
{
	int	status;
	int	pids[2];
	int	fds[2];

	if (pipe(fds) == -1)
		return ;
	pids[0] = run_pipe(all, root, fds, 1);
	if (pids[0] == -1)
		return ;
	pids[1] = run_pipe(all, root, fds, 2);
	if (pids[1] == -1)
		return ;
	close(fds[0]);
	close(fds[1]);
	wait(&status);
	wait(&status);
}

void	ft_exec(t_all *all, t_tree *root, int n)
{
	int out;
	int	p[2];

	if (!root)
		return ;
	if (root->token == COMMAND)
	{
		ft_parse_cmd(all, root->cmd);
		if (root->is_builtin == 0)
		{
			if (n)
			{
				if (root->ofd > 0)
				{
					close(1);
					dup(root->ofd);
				}
				if (root->ifd > 0)
				{
					close(0);
					dup(root->ifd);
				}
				if (root->infile && root->ifd < 0)
				{
					all->status = 1;
					exit(1);
				}
				execve(root->path, root->cmd, all->env);
				ft_print_error("MiniShell: ", root->cmd[0], ": is a directory\n");
				all->status = 1;
				exit(1);
			}
			else
			{
				if (fork() == 0)
				{
					if (root->ofd > 0)
					{
						close(1);
						dup(root->ofd);
					}
					if (root->ifd > 0)
					{
						close(0);
						dup(root->ifd);
					}
					close(root->ofd);
					close(root->ifd);
					if (!root->exist || (root->infile && root->ifd < 0))
					{
						all->status = 1;
						exit(1);
					}
					execve(root->path, root->cmd, all->env);
					ft_print_error("MiniShell: ", root->cmd[0], ": is a directory\n");
					all->status = 1;
					exit(1);
				}
				close(root->ifd);
				close(root->ofd);
				wait(&all->status);
			}
		}
		else
		{
			if (root->ofd > 0)
			{
				out = dup(1);
				close(1);
				dup(root->ofd);
			}
			ft_exec_builtin(all, root);
			dup2(out , 1);
		}
	}
	if (root->token == PIPE)
	{
		run_pipeline(all, root);
	}
	if (root->token == AND)
	{
		ft_exec(all, root->left, 0);
		if (all->status == 0)
			ft_exec(all, root->right, 0);
	}
	if (root->token == OR)
	{
		ft_exec(all, root->left, 0);
		if (all->status != 0)
			ft_exec(all, root->right, 0);
	}

}

/* **************************** INIT FUNCTIONS **************************** */
void	ft_env_init(t_env **env, char *e[])
{
	int	i;
	int j;

	i = 0;
	env[0] = NULL;
	// if (!e[0])
	// {
	// 	printf("ERROR : cannot work without env\n");
	// 	exit(EXIT_FAILURE);
	// }
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
	char	*tmp;

	root = NULL;
	str = ft_strtrim(str, " \n\t\r\n\v", &all->g_head);
	ft_fill_tree(all, &root, str, NULL);
	if(ft_check_tree(root))
	{
		printf("MiniShell: syntax error\n");
		return ;
	}
	tmp = ft_get_env(all->env_head, "PATH");
	paths = ft_split(tmp, ':');
	free (tmp);
	ft_check_tree3(root, paths, &all->g_head);
	free_tab(paths);
	all->root = root;
	all->env = NULL;
	ft_list_to_array(all);
	all->last_fd = 0;
	ft_exec(all, all->root, 0);
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
				printf ("MiniShell: syntax error near unexpected token `%c'\n", str[i]);
				return (1);
			}
		}
		else
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
			printf ("MiniShell: syntax error near unexpected token `%c'\n", c);
			return (1);
		}
		if (get == c)
		{
			(*cp)++;
			if (*cp == 2)
			{
				printf ("MiniShell: syntax error near unexpected token `%c'\n", c);
				return (1);
			}
		}
	}
	if (get == '&' && *cp == 0)
	{
		printf ("MiniShell: syntax error near unexpected token `&'\n");
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

int	ft_valid_parenthesis_mini(char *str, int *i, int *cp)
{
	int tmp;

	tmp = 0;
	while (str[*i] && *cp > 0)
	{
		if (str[*i] == '&' || str[*i] == '|')
			tmp++;
		if (str[*i] == 40)
			(*cp)++;
		if (str[*i] == 41)
			(*cp)--;
		if (*cp)
			(*i)++;
	}
	if (tmp)
		return (1);
	return (0);
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
			printf ("MiniShell: syntax error near unexpected token `%c'\n", str[i]);
			return (1);
		}
		if (str[i] == 40)
		{
			cp++;
			i++;
			if (!ft_valid_parenthesis_mini(str, &i, &cp))
			{
				printf ("MiniShell: syntax error near unexpected token `%c'\n", str[i]);
				return (1);
			}
		}
		if (cp !=0)
		{
			printf ("MiniShell: syntax error near unexpected token `%c'\n", str[i]);
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
t_all	all;

void handel_ctl(int sig)
{
	if (!all.status_s)
	{
		signal(SIGINT, &handel_ctl);
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}
/* **************************** main **************************** */

int main(int ac, char *av[], char *env[])
{
	char	*str;

	if (!env[0])
	{
		env = malloc(1 * sizeof(char*));
		env[0] = 0;
	}
	ft_env_init(&all.env_head, env);
	signal(SIGINT, &handel_ctl);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		all.status_s = 0;
		str = readline("\033[0;36m\e[1mMiniShell > \e[0m\033[0m");
		if (!str)
			return(printf("Exit\n"), 1);
		add_history(str);
		if(ft_check_syntax(str) || !ft_strcmp(str, "\0"))
			continue ;
		all.g_head = NULL;
		all.status_s = 1;
		all.root = NULL;
		ft_tree_init(str, &all);
		free(str);
		ft_close_fd(all.root);
		ft_free_garbage(all.g_head);
	}
	return (0);
}

