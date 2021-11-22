/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 19:04:53 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/22 11:28:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*list;

	if (!lst || !f || !del)
		return (NULL);
	list = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (!new)
			ft_lstclear(&list, (*del));
		ft_lstadd_back(&list, new);
		lst = lst->next;
	}
	return (list);
}
