/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:55:49 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/21 11:18:03 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*ft_alloc_tab(t_stack *a, int size)
{
	int	*tab;
	int	i;

	tab = (int *)malloc(size * sizeof(int));
	if (!tab)
		return (NULL);
	i = 0;
	while (a)
	{
		tab[i] = a->value;
		i++;
		a = a->next;
	}
	return (tab);
}

static void	ft_sort_tab(int *tab, int size)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] > tab[j])
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void ft_index_stack(t_stack *a)
{
	int	*tab;
	int	size;
	int	i;

	size = ft_lstcount(a);
	tab = ft_alloc_tab(a, size);
	ft_sort_tab(tab , size);
	while (a)
	{
		i = 0;
		while (i < size)
		{
			if(a->value == tab[i])
			{
				a->index = i;
				break ;
			}
			i++;
		}
		a = a->next;
	}
}
