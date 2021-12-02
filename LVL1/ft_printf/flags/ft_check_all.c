/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:13:46 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/01 18:04:10 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static t_print	*ft_alloc_list(void)
{
	t_print	*new;

	new = (t_print *)malloc(sizeof(t_print));
	if (!new)
		return (NULL);
	return (new);
}

static int	ft_check_flags(char c)
{
	return (c == '0' || c == '-' || c == '#' || c == ' ' || c == '+');
}

static int	ft_check_conversion(char c)
{
	return (c == 'c' || c == 's' || c == 'p'
		|| c == 'd' || c == 'i' || c == 'u' || c == 'x'
		|| c == 'X' || c == '%');
}

static int	ft_check_precision(const char *str, int *n, int *is_p)
{
	int	i;
	int	rst;

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

t_print	*ft_check_all(const char *str, int *start, char *portion)
{
	t_print	*new;
	int		i;

	new = ft_alloc_list();
	new->portion = portion;
	new->is_p = 0;
	new->next = NULL;
	i = 0;
	while (str[i] && ft_check_flags(str[i]))
		i++;
	new->flags = ft_substr(str, 0, i);
	new->width = ft_atoi(str + i);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	new->precision = ft_check_precision(str + i, &i, &new->is_p);
	if (ft_check_conversion(str[i]))
		new->conversion = str[i];
	else
	{
		new->conversion = '\0';
		return (new);
	}
	*start = *start + i + 1;
	return (new);
}
