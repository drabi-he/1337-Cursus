/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prepare_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:27:54 by hdrabi            #+#    #+#             */
/*   Updated: 2022/12/02 14:21:05 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_can_swap(t_stack *a)
{
	t_stack	test1;
	t_stack	test2;
	int		cp1;
	int		cp2;

	test1.next = &test2;
	test1.index = a->next->index;
	test2.next = a->next->next;
	test2.index = a->index;
	cp1 = ft_get_max_loop(a, 0);
	cp2 = ft_get_max_loop(&test1, 0);
	if (cp2 > cp1)
		return (1);
	return (0);
}

static int	ft_loop_list(t_stack *first, t_stack *start, int active)
{
	t_stack	*big;
	int		ref;
	int		cp;

	cp = 0;
	ref = -1;
	big = start;
	while (big)
	{
		if (active)
			big->keep = 0;
		if (big->index > ref)
		{
			ref = big->index;
			cp++;
			if (active)
				big->keep = 1;
		}
		big = big->next;
		if (!big)
			big = first;
		if (big == start)
			break ;
	}
	return (cp);
}

int	ft_get_max_loop(t_stack *a, int active)
{
	t_stack	*loop;
	t_stack	*keeper;
	int		max_loop;
	int		cp;

	max_loop = 0;
	loop = a;
	while (loop)
	{
		cp = ft_loop_list(a, loop, 0);
		if (cp > max_loop)
		{
			max_loop = cp;
			keeper = loop;
		}
		loop = loop->next;
	}
	if (active)
		ft_loop_list(a, keeper, 1);
	return (max_loop);
}

static t_stack	*ft_closest_to_top(t_stack *a, int cur_grp, int grp_size)
{
	t_stack	*closest;
	t_stack	*current;
	int		dist;
	int		current_dist;

	closest = NULL;
	current = a;
	dist = 1000;
	while (current)
	{
		if (current->index <= cur_grp * grp_size && !current->keep)
		{
			current_dist = ft_dist_to_top(a, current->index);
			if (ft_abs(current_dist) < dist)
			{
				dist = current_dist;
				closest = current;
			}
			if (dist == 0)
				break ;
		}
		current = current->next;
	}
	return (closest);
}

void	ft_prepare_a(t_stack **a, t_stack **b, t_utils *u, int cur_gp)
{
	t_stack	*tmp;
	int		tmp_dist;

	while (u->lst_size >= u->max_loop && u->group_cp + 1 >= cur_gp)
	{
		tmp = ft_closest_to_top(a[0], cur_gp, u->group_size);
		if (!tmp && ++cur_gp)
			continue ;
		tmp_dist = ft_dist_to_top(a[0], tmp->index);
		if (a && ft_can_swap(a[0]))
		{
			ft_swap_a(a, 1);
			u->max_loop = ft_get_max_loop(a[0], 1);
		}
		else if (a && !a[0]->keep && tmp_dist == 0)
		{
			ft_push_b(a, b, 1);
			u->lst_size--;
		}
		else if (u->group_cp == 1)
			ft_rr(a, b, 1);
		else
			ft_rotator(a, b, ft_min_val(1, ft_max_val(-1, tmp_dist)), 0);
	}
}
