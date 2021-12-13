/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:09:01 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/13 15:51:03 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_stack
{
	int				value;
	struct s_stack	*next;
}	t_stack;

// utils
int	ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9') || c == '-');
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

int	ft_atoi(const char *str)
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

t_stack	*ft_newnode(int value)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if(!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

int	ft_lst_count(t_stack *lst)
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
	tmp = lst[0];
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstadd_front(t_stack **lst, t_stack *new)
{
	if (!new)
		return;
	new->next = lst[0];
	lst[0] = new;
}

// check valid input (only integers)
void	ft_check_valid_input(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]) || (args[i][j] == '-' && (j != 0 || !args[i][j + 1])))
			{
				printf("%d\n",ft_isdigit(args[i][j]));
				printf("%s\n",args[i]);
				write(1, "ERROR", 5);
				exit (0);
			}
			j++;
		}
		i++;
	}
}

//check valid values (no doubles)
void	ft_check_double(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (!ft_strcmp(args[i], args[j]))
			{
				printf("%d\n",ft_strcmp(args[i], args[j]));
				printf("%s | %s\n",args[i], args[j]);
				write(1, "ERROR", 5);
				exit (0);
			}
			j++;
		}
		i++;
	}
}

t_stack	*ft_fill_lst(char **args)
{
	t_stack	*tmp;
	t_stack	*list;
	int		i;

	i = 1;
	list = NULL;
	while (args[i])
	{
		tmp = ft_newnode(ft_atoi(args[i]));
		ft_lstadd_back(&list, tmp);
		i++;
	}
	return (list);
}

//swap functions
void	ft_swap_top(t_stack *lst)
{
	int	tmp;

	if (ft_lst_count(lst) < 2)
		return ;
	tmp = lst->value;
	lst->value = lst->next->value;
	lst->next->value = tmp;
}

void	ft_push_top(t_stack **lst1, t_stack **lst2)
{

	if (!ft_lst_count(lst1[0]))
		return ;
	ft_lstadd_front(lst2, ft_newnode(lst1[0]->value));
	free(lst1[0]);
	lst1[0] = lst1[0]->next;
}

void	ft_rotate_stack(t_stack **lst)
{
	ft_lstadd_back(lst, ft_newnode(lst[0]->value));
	free(lst[0]);
	lst[0] = lst[0]->next;
}

void	ft_reverse_rotate(t_stack **lst)
{
	t_stack	*tmp;

	tmp = lst[0];
	while(tmp->next->next)
		tmp = tmp->next;
	ft_lstadd_front(lst, ft_newnode(tmp->next->value));
	free(tmp->next);
	tmp->next = NULL;
}

t_stack	*ft_devide_args(char **args)
{
	ft_check_valid_input(args);
	ft_check_double(args);
	return (ft_fill_lst(args));
}

int	main(int ac, char *av[])
{
	t_stack	*rst;
	t_stack	*test;

	rst = ft_devide_args(av);
	while(rst)
	{
		printf(" %5d |\n",rst->value);
		rst = rst->next;
	}
	return (ac);
}
