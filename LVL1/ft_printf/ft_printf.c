/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:14:12 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/27 12:29:34 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_print	*rst;
	int		valid;
	int		len;

	len = 0;
	va_start(args,str);
	rst = ft_devide(str);
	valid = ft_check_valid(rst);
	if (!valid)
	{
		while (rst)
		{
			free_all(rst);
			rst = rst->next;
		}
		return (-1);
	}
	ft_get_results(rst, args, &len);
	/*while (rst)
	{
		printf("\n*************************\n");
		printf(" portion = %s\n",rst->portion);
		printf(" flags = %s\n",rst->flags);
		printf(" width = %d\n",rst->width);
		printf(" is_p = %d\n",rst->is_p);
		printf(" precision = %d\n",rst->precision);
		printf(" conversion = %c\n",rst->conversion);
		printf(" next = %p\n",rst->next);
		rst = rst->next;
	}*/
	va_end(args);
	return (len);
}




