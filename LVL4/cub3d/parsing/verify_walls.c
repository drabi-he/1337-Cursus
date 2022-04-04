/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 14:14:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/31 17:28:34 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_vertical_mini(char **map, int i, int *j)
{
	while (map[i][*j] != ' ' && map[i][*j])
		(*j)++;
	if (map[i][*j - 1] != '1')
		ft_error("Error: map not enclosed\n", 1);
}

static void	check_vertical(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ')
				j++;
			if (map[i][j] != '1')
				ft_error("Error: map not enclosed\n", 1);
			else
				check_vertical_mini(map, i, &j);
			if (map[i][j])
				j++;
		}
		i++;
	}
}

static void	check_horizontal(char **map, int w)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (j < w)
	{
		i = 0;
		while (map[i] && j < ft_strlen(map[i]))
		{
			while (map[i] && map[i][j] == ' ')
				i++;
			if (map[i][j] != '1' && map[i - 1][j] != '\0')
				ft_error("1 -Error: map not enclosed\n", 1);
			while (map[i] && map[i][j] != ' ')
				i++;
			if (map[i - 1][j] != '1' && map[i - 1][j] != '\0')
				ft_error("2 - Error: map not enclosed\n", 1);
			while (map[i] && map[i][j] == ' ')
				i++;
		}
		j++;
	}
}

void	check_walls(t_all *all)
{
	check_vertical(all->map);
	check_horizontal(all->map, all->max_width);
}
