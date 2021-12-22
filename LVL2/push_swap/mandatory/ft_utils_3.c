/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:39:18 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/22 17:23:40 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_utils_init(t_stack *a, t_utils *u)
{
	u->lst_size = ft_lstcount(a);
	u->max_size = u->lst_size;
	if (u->lst_size > 150)
		u->group_cp = u->lst_size / 150;
	else
		u->group_cp = 1;
	u->group_size = u->lst_size / u->group_cp;
	u->max_loop = ft_get_max_loop(a, 1);
}

void	ft_sort(t_stack **a, t_stack **b)
{
	t_utils	u;
	int		current_group;

	ft_utils_init(a[0], &u);
	current_group = 1;
	ft_prepare_a(a, b, &u, current_group);
	ft_last_step(a, b, &u);
}

void	free_list(t_stack *a)
{
	while (a)
	{
		if (a)
			free(a);
		a = a->next;
	}
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
