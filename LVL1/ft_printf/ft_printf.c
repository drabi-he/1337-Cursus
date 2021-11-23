/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:14:12 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/23 19:02:56 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list args;

	va_start(args,str);
	int ptr;
	printf("test = %c\n",'c');
	printf("test = %s\n","cgfd");
	printf("test = %p\n",&ptr);
	printf("test = %d\n",10);
	printf("test = %i\n",10);
	printf("test = %u\n",-10);
	printf("test = %x\n",10);
	printf("test = %X\n",10);
	printf("test = %%\n");
	return 0;
}

/********************* notes ************************/


