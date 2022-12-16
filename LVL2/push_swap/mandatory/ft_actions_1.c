/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:49:38 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/21 14:43:11 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap_a(t_stack **a, int print)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	ft_affiche(a[0], 0);
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
	if (print)
		write(1, "sa\n", 3);
	ft_affiche(a[0], 0);

}

void	ft_swap_b(t_stack **b, int print)
{
	t_stack	*tmp1;
	t_stack	*tmp2;

	ft_affiche(b[0] , 0);
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
	if (print)
		write(1, "sb\n", 3);
}

void	ft_push_a(t_stack **b, t_stack **a, int print)
{
	t_stack	*tmp1;

	ft_affiche(a[0] , 0);
	ft_affiche(b[0], 0);
	if (!b[0])
		return ;
	tmp1 = b[0]->next;
	ft_lstadd_front(a, b[0]);
	if (tmp1)
		tmp1->prev = NULL;
	b[0] = tmp1;
	if (print)
		write(1, "pa\n", 3);
}

void	ft_push_b(t_stack **a, t_stack **b, int print)
{
	t_stack	*tmp1;

	ft_affiche(a[0], 0);
	ft_affiche(b[0], 0);
	if (!a[0])
		return ;
	tmp1 = a[0]->next;
	ft_lstadd_front(b, a[0]);
	if (tmp1)
		tmp1->prev = NULL;
	a[0] = tmp1;
	if (print)
		write(1, "pb\n", 3);
}

void	ft_ss(t_stack **a, t_stack **b, int print)
{
	ft_swap_a(a, 0);
	ft_swap_b(b, 0);
	if (print)
		write(1, "ss\n", 3);
}
