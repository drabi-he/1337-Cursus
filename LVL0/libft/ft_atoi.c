/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:33:40 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/03 12:47:31 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
int ft_atoi(const char *str)
{
	int i;
	int sign;
	int rst;

	i = 0;
	sign = 1;
	rst = 0;
	while(str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
			|| str[i] == '\v' || str[i] == '\r' || str[i] == '\t' )
	i++;
	if(str[i] == '-' || str[i] == '+')
	{
		if(str[i] == '-')
			sign *= -1;
		i++;
	}
	while(str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rst = rst*10 + str[i] - '0';
		i++;
	}
	return (sign * rst);
}
