/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:00:21 by hdrabi            #+#    #+#             */
/*   Updated: 2022/02/21 11:33:07 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"


int main(int ac, char *av[])
{
	t_all all;

	if (ac < 5 || ac > 6)
		exit(ft_putstr("Error : Wrong Number Of Arguments!!\n", 1));
	if (ft_parse_args(&all, av))
		exit(ft_putstr("Error : Wrong Arguments Format!!\n", 1));
	ft_exec(&all);

	return (0);
}
