/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 22:29:22 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/16 01:44:43 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_doors(char **map, float x, float y)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == 'D' && (f_abs(i - x) <= 2 && f_abs(j - y) <= 2))
				map[i][j] = 'O';
			if (map[i][j] == 'O' && (f_abs(i - x) >= 3 || f_abs(j - y) >= 3))
				map[i][j] = 'D';
		}
	}
}

void	choose_color(t_win *win, float x, float y, char c)
{
	(c == '1' && scale_mini(win, x, y, 0xFFFFFF));
	(c == '0' && scale_mini(win, x, y, 0x525E75));
	(c == 'F' && scale_mini(win, x, y, 0xFFFF00));
	(c == 'T' && scale_mini(win, x, y, 0xFF9900));
	(c == 'D' && scale_mini(win, x, y, 0xFF0000));
	(c == 'O' && scale_mini(win, x, y, 0x00FF00));
}
