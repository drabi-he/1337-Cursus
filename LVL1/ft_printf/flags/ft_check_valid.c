/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_valid.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 12:56:42 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/27 13:17:28 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_check_flags_error(char *flag, char c)
{
	if (!ft_strcmp(flag, "") || !ft_strcmp(flag, "-")
		|| (!ft_strcmp(flag, "-0") && (c == 's'))
		|| (!ft_strcmp(flag, "0") && c != 'c' && c != 's' && c != 'p')
		|| (!ft_strcmp(flag, "#") && (c == 'X' || c == 'x' || c == '%'))
		|| (!ft_strcmp(flag, " ") && (c == 'd' || c == 'i' || c == '%' || c == 's'))
		|| (!ft_strcmp(flag, "+") && (c == 'd' || c == 'i' || c == '%')))
		return (1);
	return (0);
}

int	ft_check_valid(t_print *lst)
{
	t_print	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!ft_check_flags_error(lst->flags, lst->conversion) && (!tmp->conversion && !tmp->next))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
