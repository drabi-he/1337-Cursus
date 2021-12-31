/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:54:55 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/31 12:04:54 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_anim_collect(t_vars *vars, int k)
{
	int	i;
	int	j;

	i = 0;
	if (!vars->collect)
		return ;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'C')
				mlx_put_image_to_window(vars->mlx,
					vars->win, vars->img_collect[k], 50 * j, 50 * i);
			j++;
		}
		i++;
	}
}

static void	ft_anim_door(t_vars *vars, int k)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'E')
				mlx_put_image_to_window(vars->mlx,
					vars->win, vars->img_exit[k], 50 * j, 50 * i);
			j++;
		}
		i++;
	}
}

int	anim(t_vars *vars)
{
	static int	k;
	static int	j;

	while (1)
	{
		usleep(80000);
		ft_anim_collect(vars, k);
		k++;
		if (k == 8)
			k = 0;
		if (vars->exit == 1)
		{
			if (j < 6)
				ft_anim_door(vars, j);
			else
				vars->exit = 0;
			j++;
		}
		break ;
	}
	return (0);
}
