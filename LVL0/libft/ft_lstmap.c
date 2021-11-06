/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:04:53 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/06 19:56:45 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*k;
	int		i;
	t_list	*p;

	if (!lst)
		return (NULL);
	i = ft_lstsize(lst);
	while(i)
	{
		p = lst->next;
		k = ft_lstnew((*f)(lst->content));
		i--;
		(*del)(lst->content);
		k = p;
	}
	k->next = 0;
	return (k);
}
