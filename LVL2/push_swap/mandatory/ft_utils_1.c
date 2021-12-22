/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:21:52 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/22 17:48:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isdigit(char c)
{
	return ((c >= '0' && c <= '9') || c == '-');
}

int	ft_min_val(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

int	ft_max_val(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static void	ft_check_interval(long nb, int sign)
{
	if (nb > 2147483647)
	{
		if (nb == 2147483648 && sign == -1)
			return ;
		write(1, "Error\n", 6);
		exit(0);
	}
}

long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	rst;

	i = 0;
	sign = 1;
	rst = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\t' )
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rst = rst * 10 + str[i] - '0';
		ft_check_interval(rst, sign);
		i++;
	}
	return (sign * rst);
}
