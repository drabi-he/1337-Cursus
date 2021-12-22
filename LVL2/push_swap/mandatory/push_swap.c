/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:47:50 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/22 14:14:41 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char *av[])
{
	t_stack	*a;
	t_stack	*b;
	char	**str;

	str = ft_split(ft_strjoin(ac, av, " "), ' ');
	a = ft_devide_args(str);
	if (ft_check_sort(a))
		exit(0);
	ft_index_stack(a);
	ft_sort(&a, &b);
	free_list(a);
	ft_affiche(a);
	ft_affiche(b);
	return (ac);
}
