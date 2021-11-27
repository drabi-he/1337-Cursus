/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:46:36 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/26 19:05:10 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../ft_printf.h"

t_print *ft_new_node(char *str, char *flags,int width, char conversion, int is_p, int precision)
{
	t_print	*new;
	new = (t_print *)malloc(sizeof(t_print));
	if (!new)
		return (NULL);
	new->portion = str;
	new->flags = flags;
	new->width = width;
	new->is_p = is_p;
	new->precision = precision;
	new->conversion = conversion;
	new->next = NULL;
	return (new);
}

void	ft_lst_back(t_print **lst, t_print *new)
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

t_print	*ft_create_lst(t_print **lst, const char *str)
{
	t_print	*node;
	int		i;
	int 	start;
	char	*portion;
	int		is_p;

	i = 0;
	start = 0;
	is_p = 0;
	while (str[i])
	{
		if (str[i] == '%' || !str[i + 1])
		{
			if(!str[i + 1] && str[i] != '%')
				portion = ft_substr(str,start,i - start + 1);
			else
				portion = ft_substr(str,start,i - start);
			node = ft_check_all(str + i + 1,&i,portion,is_p);
			start = i + 1;
			ft_lst_back(lst,node);
		}
		i++;
	}
	return (lst[0]);
}
