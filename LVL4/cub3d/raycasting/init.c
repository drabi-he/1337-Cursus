/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:52:49 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/04 20:25:02 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	ft_init_player(char	**map, float *x, float *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NEWS", map[i][j]))
			{
				*x = (float)i;
				*y = (float)j;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

void	vars_init(t_ray *ray, int x)
{
	ray->camera = 2 * x / (float)SCREEN_W - 1;
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = f_abs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = f_abs(1 / ray->ray_dir_y);
	ray->hit = 0;
}

void	initial_dist(t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

void	wall_collision(t_ray *ray, char **map)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_x][ray->map_y] > '0' \
			&& map[ray->map_x][ray->map_y] < '9')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(SCREEN_H / ray->wall_dist);
}

void	ray_init(t_ray	*ray, char **map)
{
	int	i;

	ft_init_player(map, &ray->pos_x, &ray->pos_y);
	ray->dir_x = -1;
	ray->dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0.66;
	ray->buffer = malloc(SCREEN_H * sizeof(unsigned int *));
	if (!ray->buffer)
		ft_error("Error: allocation failed\n", 1);
	i = -1;
	while (++i < SCREEN_H)
	{
		ray->buffer[i] = malloc(SCREEN_W * sizeof(unsigned int));
		if (!ray->buffer[i])
			ft_error("Error: allocation failed\n", 1);
	}
	load_texture(ray);
}
