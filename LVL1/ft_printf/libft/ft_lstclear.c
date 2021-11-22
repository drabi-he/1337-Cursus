/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:56:25 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/22 11:22:49 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*cp;

	if(!lst[0] || !del)
		return ;
	cp = lst[0];
	while (cp->next)
	{
		tmp = cp->next;
		(*del)(cp->content);
		free(cp);
		cp = tmp;
	}
	(*del)(cp->content);
	free(cp);
	lst[0] = NULL;
}
