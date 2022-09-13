/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 00:22:53 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/13 11:47:51 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	vars_init(t_ray *ray, int x)
{
	ray->camera = 2 * x / (float)SCREEN_W - 1;
	ray->ray_dir[X] = ray->dir[X] + ray->plane[X] * ray->camera;
	ray->ray_dir[Y] = ray->dir[Y] + ray->plane[Y] * ray->camera;
	ray->map[X] = (int)ray->pos[X];
	ray->map[Y] = (int)ray->pos[Y];
	if (ray->ray_dir[X] == 0)
		ray->delta_dist[X] = 1e30;
	else
		ray->delta_dist[X] = f_abs(1 / ray->ray_dir[X]);
	if (ray->ray_dir[Y] == 0)
		ray->delta_dist[Y] = 1e30;
	else
		ray->delta_dist[Y] = f_abs(1 / ray->ray_dir[Y]);
	ray->hit = 0;
}

void	initial_dist(t_ray *ray)
{
	if (ray->ray_dir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_dist[X] = (ray->pos[X] - ray->map[X]) * ray->delta_dist[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->side_dist[X] = (ray->map[X] + 1.0 - ray->pos[X]) \
		* ray->delta_dist[X];
	}
	if (ray->ray_dir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_dist[Y] = (ray->pos[Y] - ray->map[Y]) * ray->delta_dist[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->side_dist[Y] = (ray->map[Y] + 1.0 - ray->pos[Y]) \
		* ray->delta_dist[Y];
	}
}

void	wall_collision(t_ray *ray, char **map)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			ray->map[X] += ray->step[X];
			ray->tex_num = 1;
			if (ray->ray_dir[X] > 0)
				ray->tex_num = 0;
			ray->side = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			ray->map[Y] += ray->step[Y];
			ray->tex_num = 3;
			if (ray->ray_dir[Y] > 0)
				ray->tex_num = 2;
			ray->side = 1;
		}
		if (map[ray->map[X]][ray->map[Y]] == '1')
			ray->hit = 1;
		mini_check(ray, map[ray->map[X]][ray->map[Y]]);
	}
}

void	initial_color(t_ray *ray)
{

	if (ray->side == 0)
		ray->wall_dist = ray->side_dist[X] - ray->delta_dist[X];
	else
		ray->wall_dist = ray->side_dist[Y] - ray->delta_dist[Y];
	ray->line_height = (int)(SCREEN_H / ray->wall_dist);
	ray->draw[0] = -ray->line_height / 2 + SCREEN_H / 2;
	if (ray->draw[0] < 0)
		ray->draw[0] = 0;
	ray->draw[1] = ray->line_height / 2 + SCREEN_H / 2;
	if (ray->draw[1] >= SCREEN_H)
		ray->draw[1] = SCREEN_H - 1;
	if (ray->side == 0)
		ray->wall_x = ray->pos[Y] + ray->wall_dist * ray->ray_dir[Y];
	else
		ray->wall_x = ray->pos[X] + ray->wall_dist * ray->ray_dir[X];
	ray->wall_x -= floor(ray->wall_x);
	ray->tex[X] = (int)(ray->wall_x * (float)T_W);
	ray->steps = 1.0 * T_H / ray->line_height;
	ray->tex_pos = (ray->draw[0] - SCREEN_H / 2 + \
		ray->line_height / 2) * ray->steps;
}

void	initial_color_2(t_win *win, t_ray *ray)
{
	int	i;

	i = 0;
	while (i < ray->draw[0])
		ray->buffer[i++][win->x] = ray->ceiling;
	while (i < ray->draw[1])
	{
		ray->tex[Y] = (int)ray->tex_pos & (T_H - 1);
		ray->tex_pos += ray->steps;
		ray->color = get_color(&ray->t[ray->tex_num], ray->tex[X], ray->tex[Y]);
		ray->buffer[i][win->x] = ray->color;
		i++;
	}
	while (i < SCREEN_H)
		ray->buffer[i++][win->x] = ray->floor;
	if (win->mode == BONUS)
		ray->z_buffer[win->x] = ray->wall_dist;
}
