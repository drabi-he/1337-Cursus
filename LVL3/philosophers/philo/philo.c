/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:42:08 by hdrabi            #+#    #+#             */
/*   Updated: 2022/02/21 10:33:40 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_all	all;

	if (ac < 5 || ac > 6)
		return (ft_putstr("Error : Wrong Number Of Arguments!!\n", 1));
	if (ft_parse_args(&all, av))
		return (ft_putstr("Error : Wrong Arguments Format!!\n", 1));
	if (ft_exec(&all))
		return (ft_putstr("Error : failed to create thread!!\n", 1));
	ft_free_list(&all);
	return (0);
}
