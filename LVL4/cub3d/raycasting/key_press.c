/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:29:38 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/02 12:46:48 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	moveset_1(t_ray *ray, char **map, int key)
{
	if (key == 13)
	{
		if (map[(int)(ray->pos_x + ray->dir_x * MOVE_SPEED)] \
			[(int)ray->pos_y] == '0')
			ray->pos_x += ray->dir_x * MOVE_SPEED;
		if (map[(int)ray->pos_x] \
			[(int)(ray->pos_y + ray->dir_y * MOVE_SPEED)] == '0')
			ray->pos_y += ray->dir_y * MOVE_SPEED;
	}
	if (key == 1)
	{
		if (map[(int)(ray->pos_x - ray->dir_x * MOVE_SPEED)] \
			[(int)ray->pos_y] == '0')
			ray->pos_x -= ray->dir_x * MOVE_SPEED;
		if (map[(int)ray->pos_x] \
			[(int)(ray->pos_y - ray->dir_y * MOVE_SPEED)] == '0')
			ray->pos_y -= ray->dir_y * MOVE_SPEED;
	}
}

void	moveset_2(t_ray *ray, int key)
{
	if (key == 2)
	{
		ray->old_pos_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(-ROT_SPEED) \
			- ray->dir_y * sin(-ROT_SPEED);
		ray->dir_y = ray->old_pos_x * sin(-ROT_SPEED) \
			+ ray->dir_y * cos(-ROT_SPEED);
		ray->old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(-ROT_SPEED) \
			- ray->plane_y * sin(-ROT_SPEED);
		ray->plane_y = ray->old_plane_x * sin(-ROT_SPEED) \
			+ ray->plane_y * cos(-ROT_SPEED);
	}
}

void	moveset_3(t_ray *ray, int key)
{
	if (key == 0)
	{
		ray->old_pos_x = ray->dir_x;
		ray->dir_x = ray->dir_x * cos(ROT_SPEED) \
			- ray->dir_y * sin(ROT_SPEED);
		ray->dir_y = ray->old_pos_x * sin(ROT_SPEED) \
			+ ray->dir_y * cos(ROT_SPEED);
		ray->old_plane_x = ray->plane_x;
		ray->plane_x = ray->plane_x * cos(ROT_SPEED) \
			- ray->plane_y * sin(ROT_SPEED);
		ray->plane_y = ray->old_plane_x * sin(ROT_SPEED) \
			+ ray->plane_y * cos(ROT_SPEED);
	}
}

int	key_press(int key, t_all *all)
{
	t_ray	*ray;

	ray = &all->ray;
	mlx_clear_window(all->win.mlx, all->win.win);
	moveset_1(ray, all->map, key);
	moveset_2(ray, key);
	moveset_3(ray, key);
	draw_screen(&all->ray, &all->win, all->map);
	return (0);
}
