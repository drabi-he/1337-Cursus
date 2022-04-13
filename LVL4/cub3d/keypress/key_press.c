/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:39:04 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/08 22:29:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	moveset_1(t_ray *ray, char **map, t_key key)
{
	if (key.w == 1)
	{
		if (map[(int)(ray->pos[X] + ray->dir[X] * key.move_speed)] \
			[(int)ray->pos[Y]] == '0' || map[(int)(ray->pos[X] + \
			ray->dir[X] * key.move_speed)][(int)ray->pos[Y]] == 'O')
			ray->pos[X] += ray->dir[X] * key.move_speed;
		if (map[(int)ray->pos[X]][(int)(ray->pos[Y] + ray->dir[Y] \
		* key.move_speed)] == '0' || map[(int)ray->pos[X]] \
		[(int)(ray->pos[Y] + ray->dir[Y] * key.move_speed)] == 'O')
			ray->pos[Y] += ray->dir[Y] * key.move_speed;
	}
	if (key.s == 1)
	{
		if (map[(int)(ray->pos[X] - ray->dir[X] * key.move_speed)] \
			[(int)ray->pos[Y]] == '0' || map[(int)(ray->pos[X] - \
			ray->dir[X] * key.move_speed)][(int)ray->pos[Y]] == 'O')
			ray->pos[X] -= ray->dir[X] * key.move_speed;
		if (map[(int)ray->pos[X]][(int)(ray->pos[Y] - ray->dir[Y] \
		* key.move_speed)] == '0' || map[(int)ray->pos[X]] \
		[(int)(ray->pos[Y] - ray->dir[Y] * key.move_speed)] == 'O')
			ray->pos[Y] -= ray->dir[Y] * key.move_speed;
	}
}

void	moveset_2(t_ray *ray, char **map, t_key key)
{
	if (key.d == 1)
	{
		if (map[(int)(ray->pos[X] + ray->plane[X] * key.move_speed)] \
			[(int)ray->pos[Y]] == '0' || map[(int)(ray->pos[X] + \
			ray->plane[X] * key.move_speed)][(int)ray->pos[Y]] == 'O')
			ray->pos[X] += ray->plane[X] * key.move_speed;
		if (map[(int)ray->pos[X]][(int)(ray->pos[Y] + ray->plane[Y] \
		* key.move_speed)] == '0' || map[(int)ray->pos[X]][(int)(ray->pos[Y] \
		+ ray->plane[Y] * key.move_speed)] == 'O')
			ray->pos[Y] += ray->plane[Y] * key.move_speed;
	}
	if (key.a == 1)
	{
		if (map[(int)(ray->pos[X] - ray->plane[X] * key.move_speed)] \
			[(int)ray->pos[Y]] == '0' || map[(int)(ray->pos[X] - ray->plane[X] \
			* key.move_speed)][(int)ray->pos[Y]] == 'O')
			ray->pos[X] -= ray->plane[X] * key.move_speed;
		if (map[(int)ray->pos[X]][(int)(ray->pos[Y] - ray->plane[Y] \
		* key.move_speed)] == '0' || map[(int)ray->pos[X]][(int)(ray->pos[Y] \
		- ray->plane[Y] * key.move_speed)] == 'O')
			ray->pos[Y] -= ray->plane[Y] * key.move_speed;
	}
}

void	moveset_3(t_ray *ray, t_key key)
{
	if (key.r == 1)
	{
		ray->old_pos_x = ray->dir[X];
		ray->dir[X] = ray->dir[X] * cos(-key.rot_speed) \
			- ray->dir[Y] * sin(-key.rot_speed);
		ray->dir[Y] = ray->old_pos_x * sin(-key.rot_speed) \
			+ ray->dir[Y] * cos(-key.rot_speed);
		ray->old_plane_x = ray->plane[X];
		ray->plane[X] = ray->plane[X] * cos(-key.rot_speed) \
			- ray->plane[Y] * sin(-key.rot_speed);
		ray->plane[Y] = ray->old_plane_x * sin(-key.rot_speed) \
			+ ray->plane[Y] * cos(-key.rot_speed);
	}
}

void	moveset_4(t_ray *ray, t_key key)
{
	if (key.l == 1)
	{
		ray->old_pos_x = ray->dir[X];
		ray->dir[X] = ray->dir[X] * cos(key.rot_speed) \
			- ray->dir[Y] * sin(key.rot_speed);
		ray->dir[Y] = ray->old_pos_x * sin(key.rot_speed) \
			+ ray->dir[Y] * cos(key.rot_speed);
		ray->old_plane_x = ray->plane[X];
		ray->plane[X] = ray->plane[X] * cos(key.rot_speed) \
			- ray->plane[Y] * sin(key.rot_speed);
		ray->plane[Y] = ray->old_plane_x * sin(key.rot_speed) \
			+ ray->plane[Y] * cos(key.rot_speed);
	}
}

int	smooth_move(t_all *all)
{
	t_ray		*ray;
	t_win		*win;
	static int	i;

	ray = all->ray;
	win = all->win;
	mlx_clear_window(win->mlx, win->win);
	moveset_1(ray, all->map, all->key);
	moveset_2(ray, all->map, all->key);
	moveset_3(ray, all->key);
	moveset_4(ray, all->key);
	check_doors(all->map, all->ray->pos[X], all->ray->pos[Y]);
	while (i < 78)
	{
		i++;
		if (i == 77)
			i = 0;
		ray->anime = i / 7;
		break ;
	}
	draw_screen(ray, win, all->map, all->win->mode);
	return (0);
}
