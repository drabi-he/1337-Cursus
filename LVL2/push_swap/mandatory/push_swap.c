/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:47:50 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/06 12:27:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char *av[])
{
	t_stack	*a;
	t_stack	*b;
	char	**str;
	char	*join;

	join = ft_strjoin(ac, av, " ");
	str = ft_split(join, ' ');
	free(join);
	a = ft_devide_args(str);
	if (ft_check_sort(a))
		exit(0);
	ft_index_stack(a);
	ft_sort(&a, &b);
	ft_affiche(a, 0);
	ft_affiche(b, 0);
	free_list(a);
	return (0);
}
