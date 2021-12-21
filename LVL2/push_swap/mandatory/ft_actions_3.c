/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:25:23 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/21 14:43:57 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rr(t_stack **a, t_stack **b, int print)
{
	ft_rotate_a(a, 0);
	ft_rotate_b(b, 0);
	if (print)
		write(1, "rr\n", 3);
}

void	ft_rrr(t_stack **a, t_stack **b, int print)
{
	ft_reverse_rotate_a(a, 0);
	ft_reverse_rotate_b(b, 0);
	if (print)
		write(1, "rrr\n", 4);
}

void	ft_double_rot(t_stack **a, t_stack **b, int *rot_a, int *rot_b)
{
	while (*rot_a > 0 && *rot_b > 0)
	{
		(*rot_a)--;
		(*rot_b)--;
		ft_rr(a, b, 1);
	}
	while (*rot_a < 0 && *rot_b < 0)
	{
		(*rot_a)++;
		(*rot_b)++;
		ft_rrr(a, b, 1);
	}
}

void	ft_rotator(t_stack **a, t_stack **b, int rot_a, int rot_b)
{
	ft_double_rot(a, b, &rot_a, &rot_b);
	while (rot_a > 0)
	{
		rot_a--;
		ft_rotate_a(a, 1);
	}
	while (rot_a < 0)
	{
		rot_a++;
		ft_reverse_rotate_a(a, 1);
	}
	while (rot_b > 0)
	{
		rot_b--;
		ft_rotate_b(b, 1);
	}
	while (rot_b < 0)
	{
		rot_b++;
		ft_reverse_rotate_b(b, 1);
	}
}
