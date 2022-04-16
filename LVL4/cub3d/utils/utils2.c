/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:24:07 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/16 00:27:46 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_close(void)
{
	exit(1);
	return (0);
}

int	count_sprites(char **map)
{
	int	i;
	int	j;
	int	cp;

	i = -1;
	cp = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			((map[i][j] == 'F' || map[i][j] == 'T') && cp++);
	}
	return (cp);
}

void	mini_check(t_ray *ray, char c)
{
	if (c == 'D')
	{
		ray->hit = 1;
		ray->tex_num = 15;
	}
}
