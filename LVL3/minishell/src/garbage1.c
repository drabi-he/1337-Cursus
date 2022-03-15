/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 14:43:03 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/15 14:43:39 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_garbage	*ft_new_garbage(void **addr)
{
	t_garbage	*new;

	new = malloc(sizeof(t_garbage));
	if (!new)
		return (NULL);
	new->addr = addr;
	new->next = NULL;
	return (new);
}

void	ft_add_garbage(t_garbage **lst, t_garbage *new)
{
	t_garbage	*tmp;

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

void	ft_free_garbage(t_garbage *garbage)
{
	while (garbage)
	{
		free(garbage->addr);
		free(garbage);
		garbage = garbage->next;
	}
}
