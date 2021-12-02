/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_divide_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:31:19 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 13:23:43 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	ft_lst_back(t_print **lst, t_print *new)
{
	t_print	*cp;

	if (!new)
		return ;
	if (!lst[0])
	{
		lst[0] = new;
		return ;
	}
	cp = lst[0];
	while (cp->next)
		cp = cp->next;
	cp->next = new;
}

t_print	*ft_devide_str(const char *str)
{
	t_print	*lst;
	t_print	*node;
	int		i;
	int		start;
	char	*portion;

	i = 0;
	start = 0;
	lst = NULL;
	while (str[i])
	{
		if (str[i] == '%' || !str[i + 1])
		{
			if (!str[i + 1] && str[i] != '%')
				portion = ft_substr(str, start, i - start + 1);
			else
				portion = ft_substr(str, start, i - start);
			node = ft_check_all(str + i + 1, &i, portion);
			start = i + 1;
			ft_lst_back(&lst, node);
		}
		i++;
	}
	return (lst);
}
