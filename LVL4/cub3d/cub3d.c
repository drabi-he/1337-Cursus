/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:49:04 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/04 13:10:23 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	t_all	all;

	if (ac != 2)
		ft_error("Error: we need a map\n", 1);
	read_map(&all, av[1]);
	gameplay(&all);
	return (0);
}