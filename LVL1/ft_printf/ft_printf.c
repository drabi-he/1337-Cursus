/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:22:46 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 17:50:44 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_all(char	*str, int *len)
{
	(*len) += (int)ft_strlen((const char *)str);
	ft_putstr_fd(str, 1);
}

static void	ft_get_results(t_print *lst, va_list args, int *len)
{
	t_print	*tmp;

	tmp = lst;
	while (tmp)
	{
		ft_print_all(tmp->portion, len);
		if (tmp->conversion == 'c')
			ft_print_char(tmp, (char)va_arg(args, char *), len);
		if (tmp->conversion == 's')
			ft_print_str(tmp, va_arg(args, char *), len);
		if (tmp->conversion == 'p')
			ft_print_ptr(tmp, va_arg(args, size_t), len);
		if (tmp->conversion == 'd' || tmp->conversion == 'i')
			ft_print_dec(tmp, va_arg(args, int), len);
		if (tmp->conversion == 'u' )
			ft_print_un(tmp, va_arg(args, unsigned), len);
		if (tmp->conversion == 'x' || tmp->conversion == 'X')
			ft_print_hex(tmp, va_arg(args, unsigned), len);
		if (tmp->conversion == '%' )
			ft_print_percent(tmp, len);
		free_all(tmp);
		tmp = tmp->next;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_print	*liste;
	int		len;

	len = 0;
	va_start(args, str);
	liste = ft_devide_str(str);
	ft_get_results(liste, args, &len);
	va_end(args);
	return (len);
}
