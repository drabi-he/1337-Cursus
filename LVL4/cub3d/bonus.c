/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:17:36 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/15 21:56:23 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char *av[])
{
	t_all		all;
	t_parsing	parsing;

	all.key.move_speed = 0.11;
	all.key.rot_speed = 0.1;
	main_parse(ac, av, &parsing, BONUS);
	print_instructions(&all.key);
	init_all(&all, parsing, BONUS);
	free_parsing(&parsing);
	return (0);
}
