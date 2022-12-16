/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:24:52 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/21 11:25:13 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_rotate_a(t_stack **a, int print)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	ft_affiche(a[0], 0);
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
}

void	ft_rotate_b(t_stack **b, int print)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	ft_affiche(b[0], 0);
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
}

void	ft_reverse_rotate_a(t_stack **a, int print)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	ft_affiche(a[0], 0);
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
}

void	ft_reverse_rotate_b(t_stack **b, int print)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	ft_affiche(b[0], 0);
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
}
