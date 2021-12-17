/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:18:05 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/16 17:22:35 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_stack
{
	struct s_stack	*prev;
	int				value;
	struct s_stack	*next;
}	t_stack;

// mini-utils
int	ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9') || c == '-');
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	rst;

	i = 0;
	sign = 1;
	rst = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\t' )
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rst = rst * 10 + str[i] - '0';
		i++;
	}
	return (sign * rst);
}

int	get_min(t_stack *lst)
{
	int	min;

	min = lst->value;
	while (lst)
	{
		if (min > lst->value)
			min = lst->value;
		lst = lst->next;
	}
	return (min);
}

int	get_max(t_stack *lst)
{
	int	max;

	max = lst->value;
	while (lst)
	{
		if (max < lst->value)
			max = lst->value;
		lst = lst->next;
	}
	return (max);
}

void	ft_affiche(t_stack *lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("| %5d |\n", lst->value);
		lst = lst->next;
	}
	printf("--------------------------\n");
}

// strjoin to convert **av to 1d str
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_concta(char *dest, char *src)
{
	int	i;
	int	dest_size;

	i = 0;
	dest_size = 0;
	while (dest[dest_size])
		dest_size++;
	while (src[i])
	{
		dest[dest_size + i] = src[i];
		i++;
	}
	dest[dest_size + i] = '\0';
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		lenght;
	int		i;
	char	*concat;

	if (size > 0)
		lenght = ft_strlen(sep) * (size - 1);
	i = 1;
	while (i < size)
	{
		lenght += ft_strlen(strs[i]);
		i++;
	}
	concat = malloc(sizeof(char) * (lenght + 1));
	if (!concat)
		return (NULL);
	i = 1;
	*concat = 0;
	while (i < size)
	{
		ft_concta(concat, strs[i]);
		if (i < size - 1)
			ft_concta(concat, sep);
		i++;
	}
	return (concat);
}

// split to convert strjoin to 2d str
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

// function to manipulate linked list
t_stack	*ft_new_node(int value)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	ft_lstcount(t_stack *lst)
{
	t_stack	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_stack	*ft_lstlast(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_front(t_stack **lst, t_stack *new)
{
	if (!new)
		return ;
	new->next = lst[0];
	if (lst[0])
		lst[0]->prev = new;
	lst[0] = new;
}

void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*tmp;

	if (!new)
		return ;
	if (!lst[0])
	{
		lst[0] = new;
		return ;
	}
	tmp = ft_lstlast(lst[0]);
	tmp->next = new;
	new->prev = tmp;
}

//utils
void	ft_check_input_type(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]) || (args[i][j] == '-' && (j != 0
				|| !ft_isdigit(args[i][j + 1]))))
			{
				write(1, "Error\n", 6);
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void	ft_check_double(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (!ft_strcmp(args[i], args[j]))
			{
				write(1, "Error\n", 6);
				exit(0);
			}
			j++;
		}
		i++;
	}
}

t_stack	*ft_fill_stack(char **args)
{
	t_stack	*tmp;
	t_stack	*list;
	int		i;

	list = NULL;
	i = 0;
	while (args[i])
	{
		tmp = ft_new_node(ft_atoi(args[i]));
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	return (list);
}

t_stack	*ft_devide_args(char **args)
{
	ft_check_input_type(args);
	ft_check_double(args);
	return (ft_fill_stack(args));
}

int	ft_check_sort_asc(t_stack *lst)
{
	if (!lst)
		return (1);
	while (lst->next)
	{
		if (lst->value > lst->next->value)
			return (0);
		lst = lst->next;
	}
	return (1);
}

int	ft_check_sort_des(t_stack *lst)
{
	if (!lst)
		return (1);
	while (lst->next)
	{
		if (lst->value < lst->next->value)
			return (0);
		lst = lst->next;
	}
	return (1);
}

// swap functions
void	ft_swap_a(t_stack **a)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	if (ft_lstcount(a[0]) < 2)
		return ;
	tmp1 = a[0];
	tmp2 = a[0]->next;
	tmp2->prev = tmp1->prev;
	tmp1->prev = tmp2;
	tmp1->next = tmp2->next;
	tmp2->next = tmp1;
	a[0] = tmp2;
	if (tmp1->next)
		tmp1->next->prev = tmp1;
	write(1, "sa\n", 3);
	ft_affiche(a[0]);
}

void	ft_swap_b(t_stack **b)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	if (ft_lstcount(b[0]) < 2)
		return ;
	tmp1 = b[0];
	tmp2 = b[0]->next;
	tmp2->prev = tmp1->prev;
	tmp1->prev = tmp2;
	tmp1->next = tmp2->next;
	tmp2->next = tmp1;
	if (tmp1->next)
		tmp1->next->prev = tmp1;
	b[0] = tmp2;
	write(1, "sb\n", 3);
	ft_affiche(b[0]);
}

void	ft_push_a(t_stack **b, t_stack **a)
{
	t_stack	*tmp1;

	if (!b[0])
		return ;
	tmp1 = b[0]->next;
	ft_lstadd_front(a, b[0]);
	if (tmp1)
		tmp1->prev = NULL;
	b[0] = tmp1;
	write(1, "pa\n", 3);
	ft_affiche(a[0]);
	ft_affiche(b[0]);
}

void	ft_push_b(t_stack **a, t_stack **b)
{
	t_stack	*tmp1;

	if (!a[0])
		return ;
	tmp1 = a[0]->next;
	ft_lstadd_front(b, a[0]);
	if (tmp1)
		tmp1->prev = NULL;
	a[0] = tmp1;
	write(1, "pb\n", 3);
	ft_affiche(a[0]);
	ft_affiche(b[0]);
}

void	ft_rotate_a(t_stack **a, int print)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	if (ft_lstcount(a[0]) < 2)
		return ;
	tmp1 = a[0];
	tmp2 = a[0]->next;
	tmp2->prev = tmp1->prev;
	tmp1->prev = ft_lstlast(a[0]);
	ft_lstlast(a[0])->next = tmp1;
	tmp1->next = NULL;
	a[0] = tmp2;
	if (print)
		write(1, "ra\n", 3);
	ft_affiche(a[0]);
}

void	ft_rotate_b(t_stack **b, int print)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	if (ft_lstcount(b[0]) < 2)
		return ;
	tmp1 = b[0];
	tmp2 = b[0]->next;
	tmp2->prev = tmp1->prev;
	tmp1->prev = ft_lstlast(b[0]);
	ft_lstlast(b[0])->next = tmp1;
	tmp1->next = NULL;
	b[0] = tmp2;
	if (print)
		write(1, "rb\n", 3);
	ft_affiche(b[0]);
}

void	ft_reverse_rotate_a(t_stack **a, int print)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	if (ft_lstcount(a[0]) < 2)
		return ;
	tmp1 = ft_lstlast(a[0]);
	tmp2 = a[0];
	tmp1->prev->next = NULL;
	tmp1->prev = tmp2->prev;
	tmp2->prev = tmp1;
	tmp1->next = tmp2;
	a[0] = tmp1;
	if (print)
		write(1, "rra\n", 4);
	ft_affiche(a[0]);
}

void	ft_reverse_rotate_b(t_stack **b, int print)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	if (ft_lstcount(b[0]) < 2)
		return ;
	tmp1 = ft_lstlast(b[0]);
	tmp2 = b[0];
	tmp1->prev->next = NULL;
	tmp1->prev = tmp2->prev;
	tmp2->prev = tmp1;
	tmp1->next = tmp2;
	b[0] = tmp1;
	if (print)
		write(1, "rrb\n", 4);
	ft_affiche(b[0]);
}

void	ft_rr(t_stack **a, t_stack **b)
{
	ft_rotate_a(a, 0);
	ft_rotate_b(b, 0);
	write(1, "rr\n", 3);
}

void	ft_rrr(t_stack **a, t_stack **b)
{
	ft_reverse_rotate_a(a, 0);
	ft_reverse_rotate_b(b, 0);
	write(1, "rrr\n", 4);
}

//sorting algos

void	ft_sort(t_stack **a, t_stack **b)
{
	if (ft_lstcount(a[0]) < 6)
		printf("GFY we are working on it!!\n");
	else
		printf("GFY we are working on it!!\n");
}

int	main(int ac, char *av[])
{
	t_stack	*a;
	t_stack	*b;
	char	**str;

	//started strjoin from 1 to avoid a.out
	str = ft_split(ft_strjoin(ac, av, " "), ' ');
	a = ft_devide_args(str);
	if (ft_check_sort_asc(a))
		exit(0);
	ft_sort(&a, &b);

	ft_affiche(a);
	ft_affiche(b);
	return (ac);
}
