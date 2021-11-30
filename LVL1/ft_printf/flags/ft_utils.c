/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:14:10 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/30 17:01:10 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../ft_printf.h>

int ft_nbr_len(long long nb)
{
	int i;

	i = 0;
	if (nb <= 0)
		i++;
	while (nb != 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

int ft_check_flags(char c)
{
	return (c == '0' || c == '-' || c == '#' || c == ' ' || c == '+');
}

int ft_check_conversion(char c)
{
	return (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i' || c == 'u' || c == 'x'
		|| c == 'X' || c == '%');
}

int	ft_check_precision(const char *str,int *n,int *is_p)
{
	int i;
	int rst;

	i = 0;
	if (str[i] == '.')
	{
		*is_p = 1;
		i++;
	}
	rst = ft_atoi(str + i);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	*n += i;
	return (rst);
}

t_print	*ft_check_all(const char *str, int *start, char *portion, int is_p)
{
	int		i;
	int		width;
	char	conversion;
	char	*flags;
	int		precision;

	i = 0;
	conversion = '\0';
	while (str[i] && ft_check_flags(str[i]))
		i++;
	flags = ft_substr(str,0,i);
	width = ft_atoi(str + i);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	precision = ft_check_precision(str + i,&i,&is_p);
	if (ft_check_conversion(str[i]))
		conversion = str[i];
	else
		return (ft_new_node(portion,flags,width,'\0',is_p,precision));
	*start = *start + i + 1;
	return (ft_new_node(portion,flags,width,conversion,is_p,precision));
}
