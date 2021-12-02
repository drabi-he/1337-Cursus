/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 13:54:22 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 15:13:47 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_get_sp_count(int width, int precision, int nb_len, int nb)
{
	int	count;

	if (nb >= 0)
	{
		if (precision >= nb_len)
			count = width - precision;
		else
			count = width - nb_len;
	}
	else
	{
		if (precision >= nb_len)
			count = width - precision - 1;
		else
			count = width - nb_len ;
	}
	return (count);
}
