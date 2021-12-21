/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last_step.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:34:54 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/21 14:44:20 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_index_to_top(int index, int size)
{
	if (index >= size / 2)
		index -= size;
	return (index);
}

int	ft_insert_placement(t_stack *b, int cur_index, int size)
{
	t_stack	*last;
	t_stack	*first;
	int		max_dist[3];

	last = ft_lstlast(b);
	first = b;
	max_dist[1] = 1000;
	max_dist[2] = 0;
	while (first)
	{
		if ((last->index > first->index
				&& (cur_index < first->index || cur_index > last->index))
			|| (cur_index > last->index && cur_index < first->index))
		{
			max_dist[0] = max_dist[2];
			if (max_dist[0] > size / 2)
				max_dist[0] -= size;
			if (ft_abs(max_dist[0]) < max_dist[1])
				max_dist[1] = max_dist[0];
		}
		last = first;
		first = first->next;
		max_dist[2]++;
	}
	return (max_dist[1]);
}

void	ft_prepare_b(t_stack **b, t_stack **a, t_utils *u, int max_dist)
{
	t_stack	*tmp;
	int		dist_b;
	int		i;
	int		insert;
	int		total_dist;

	tmp = b[0];
	i = 0;
	while (tmp)
	{
		dist_b = ft_index_to_top(i++, u->max_size - u->lst_size);
		insert = ft_insert_placement(a[0], tmp->index, u->lst_size);
		total_dist = ft_abs(insert) + ft_abs(dist_b);
		if (total_dist < max_dist)
		{
			max_dist = total_dist;
			u->rot_a = insert;
			u->rot_b = dist_b;
		}
		tmp = tmp->next;
	}
}

void	ft_last_step(t_stack **a, t_stack **b, t_utils *u)
{
	while (b[0])
	{
		ft_prepare_b(b, a, u, 1000);
		ft_rotator(a, b, u->rot_a, u->rot_b);
		ft_push_a(b, a, 1);
		u->lst_size++;
	}
	ft_rotator(a, b, ft_dist_to_top(a[0], 0), 0);
}
