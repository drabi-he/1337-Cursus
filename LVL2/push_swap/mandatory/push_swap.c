/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:47:50 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/21 11:50:13 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char *av[])
{
	t_stack	*a;
	t_stack	*b;
	char	**str;

	//started strjoin from 1 to avoid a.out
	str = ft_split(ft_strjoin(ac, av, " "), ' ');
	a = ft_devide_args(str);
	if (ft_check_sort(a))
		exit(0);
	ft_index_stack(a);
	ft_sort(&a, &b);
	// ft_affiche(a);
	// ft_affiche(b);
	return (ac);
}
