/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_others.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:23:21 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/21 11:34:16 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}


void	ft_affiche(t_stack *lst)
{
	return ;
	if (!lst)
		return ;
	while (lst)
	{
		printf("| %3d | %5d | %d |\n",lst->index,lst->value,lst->keep);
		lst = lst->next;
	}
	printf("--------------------------\n");
}

int	ft_check_sort(t_stack *lst)
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

int	ft_dist_to_top(t_stack *a, int index)
{
	int	i;
	int	size;

	i = 0;
	size = ft_lstcount(a);
	while (a)
	{
		if (a->index == index)
			break;
		i++;
		a = a->next;
	}
	if (i > size / 2)
		i -= size;
	return (i);
}
