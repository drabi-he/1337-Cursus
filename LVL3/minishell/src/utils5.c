/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:38:10 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/17 13:08:14 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_skip_quote_rev(char *str, int *i)
{
	char	get;

	if (str[*i] == '\"' || str[*i] == '\'')
	{
		get = str[(*i)--];
		while (str[*i] && str[*i] != get)
			(*i)--;
		if (!str[*i])
		{
			printf("MiniShell: syntax error ");
			printf("unclosed quote near `%c'\n", str[*i]);
			return (-1);
		}
	}
	return (0);
}

void	ft_skip_par_rev(char *str, int *i)
{
	int	cp;

	cp = 0;
	if (str[*i] == 41)
	{
		cp++;
		(*i)--;
		while (str[*i] && cp > 0)
		{
			if (str[*i] == 40)
				cp--;
			if (str[*i] == 41)
				cp++;
			(*i)--;
		}
	}
}

static int	ft_alloc(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char			*rst;
	int				size;
	unsigned int	nb;

	size = ft_alloc(n) + 1;
	rst = (char *)malloc(size * sizeof(char));
	if (!rst)
		return (NULL);
	if (n < 0)
		nb = -n;
	else
		nb = n;
	rst[--size] = 0;
	while (--size >= 0 && nb)
	{
		rst[size] = '0' + nb % 10;
		nb /= 10;
	}
	if (n < 0)
		rst[0] = '-';
	if (n == 0)
		rst[0] = '0';
	return (rst);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	rst;

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
		i++;
	}
	return (sign * rst);
}
