/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:42:20 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 15:17:14 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	free_all(t_print *lst)
{
	if (lst->portion)
		free(lst->portion);
	if (lst->flags)
		free(lst->flags);
	free(lst);
}

int	ft_search_flag(char *flag, char c)
{
	int	i;

	i = 0;
	while (flag[i])
	{
		if (flag[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_ptr_null(int precision, int width, size_t addr)
{
	int	i;

	if (precision > 12)
		i = width - precision - 2;
	else
	{
		if (addr == 0)
			i = width - 2;
		else
			i = width - 14;
	}
	return (i);
}

int	ft_nbr_len(long long nb)
{
	int	i;

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

int	ft_convert_len(size_t nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		i++;
	while (nb)
	{
		nb /= 16;
		i++;
	}
	return (i);
}
