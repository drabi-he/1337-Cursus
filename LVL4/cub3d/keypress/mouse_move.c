/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 21:28:46 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/09 22:19:49 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	mouse_left(t_ray *ray, int x, int pos)
{
	if (x > pos)
	{
		ray->old_pos_x = ray->dir[X];
		ray->dir[X] = ray->dir[X] * cos(-ROT_SPEED) \
			- ray->dir[Y] * sin(-ROT_SPEED);
		ray->dir[Y] = ray->old_pos_x * sin(-ROT_SPEED) \
			+ ray->dir[Y] * cos(-ROT_SPEED);
		ray->old_plane_x = ray->plane[X];
		ray->plane[X] = ray->plane[X] * cos(-ROT_SPEED) \
			- ray->plane[Y] * sin(-ROT_SPEED);
		ray->plane[Y] = ray->old_plane_x * sin(-ROT_SPEED) \
			+ ray->plane[Y] * cos(-ROT_SPEED);
	}
}

int	ft_move(int x, int y, t_all *all)
{
	static int	pos;

	mlx_clear_window(all->win->mlx, all->win->win);
	mouse_left(all->ray, x, pos);
	if (x < pos)
	{
		all->ray->old_pos_x = all->ray->dir[X];
		all->ray->dir[X] = all->ray->dir[X] * cos(ROT_SPEED) \
			- all->ray->dir[Y] * sin(ROT_SPEED);
		all->ray->dir[Y] = all->ray->old_pos_x * sin(ROT_SPEED) \
			+ all->ray->dir[Y] * cos(ROT_SPEED);
		all->ray->old_plane_x = all->ray->plane[X];
		all->ray->plane[X] = all->ray->plane[X] * cos(ROT_SPEED) \
			- all->ray->plane[Y] * sin(ROT_SPEED);
		all->ray->plane[Y] = all->ray->old_plane_x * sin(ROT_SPEED) \
			+ all->ray->plane[Y] * cos(ROT_SPEED);
	}
	pos = x;
	draw_screen(all->ray, all->win, all->map, all->win->mode);
	return (y);
}
