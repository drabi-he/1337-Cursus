/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_results.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:36:50 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/27 17:21:52 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void free_all(t_print *lst)
{
	if (lst->portion)
		free(lst->portion);
	if (lst->flags)
		free(lst->flags);
	free(lst);
}

void ft_get_results(t_print *lst, va_list args, int *len)
{
	t_print *tmp;
	tmp = lst;
	while (tmp)
	{
		ft_print_all(tmp->portion,len);
		if (tmp->conversion == 'c')
			ft_print_char(tmp->flags,tmp->width,(char)va_arg(args,char *),len);
		if (tmp->conversion == 's')
			ft_print_str(tmp->flags,tmp->is_p,tmp->precision,tmp->width,va_arg(args,char *),len);
		if (tmp->conversion == 'p')
			ft_print_ptr(tmp->flags,tmp->is_p,tmp->precision,tmp->width,va_arg(args,size_t),len);
		free_all(tmp);
		tmp = tmp->next;
	}
}

