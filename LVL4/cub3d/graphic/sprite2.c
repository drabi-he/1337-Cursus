/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 14:44:44 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/08 16:13:50 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_sprit_locations(t_sprite **sprite, char **map)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'F')
			{
				sprite[0][k].x = i + 0.5;
				sprite[0][k].y = j + 0.5;
				sprite[0][k].texture = 4;
				k++;
			}
		}
	}
}
