/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_devide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:50:49 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/25 11:54:28 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../ft_printf.h"

t_print *ft_devide(const char *str)
{
	t_print	*liste;

	liste = ft_create_lst(&liste,str);

	return (liste);
}

