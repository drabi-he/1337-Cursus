/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandatory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:17:36 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/22 15:00:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	t_all		all;
	t_data		data;

	all.key.move_speed = 0.11;
	all.key.rot_speed = 0.1;
	parse_map(ac, av[1], &data, MANDATORY);
	print_instructions(&all.key);
	init_all(&all, data, MANDATORY);
	free_all(&data, &all);
	return (ac);
}
