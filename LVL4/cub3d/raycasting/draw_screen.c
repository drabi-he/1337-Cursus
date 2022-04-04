/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:10:30 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/04 13:41:23 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initial_color(t_win *win, t_ray *ray, char **map)
{
	ray->draw_start = -ray->line_height / 2 + SCREEN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_H / 2;
	if (ray->draw_end >= SCREEN_H)
		ray->draw_end = SCREEN_H - 1;
	ray->tex_num = map[ray->map_x][ray->map_y] - 49;
	if (ray->side == 0)
		ray->wall_x = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (float)T_W);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = T_W - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		ray->tex_x = T_W - ray->tex_x - 1;
	ray->step = 1.0 * T_H / ray->line_height;
	ray->tex_pos = (ray->draw_start - SCREEN_H / 2 + \
		ray->line_height / 2) * ray->step;
}

void	initial_color_2(t_win *win, t_ray *ray)
{
	int	i;

	i = ray->draw_start;
	while (i < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (T_H - 1);
		ray->tex_pos += ray->step;
		ray->color = ray->t[ray->tex_num].t[T_H * ray->tex_y + ray->tex_x];
		if (ray->side == 1)
			ray->color = (ray->color >> 1) & 8355711;
		ray->buffer[i][win->x] = ray->color;
		i++;
	}
}

void	print_ray(t_ray *ray)
{
	printf("pos = %f | %f\n", ray->pos_x, ray->pos_y);
	printf("dir = %f | %f\n", ray->dir_x, ray->dir_y);
	printf("plane = %f | %f\n", ray->plane_x, ray->plane_y);
	printf("camera = %f\n", ray->camera);
	printf("ray dir = %f | %f\n", ray->ray_dir_x, ray->ray_dir_y);
	printf("map = %d | %d\n", ray->map_x, ray->map_y);
	printf("step = %d | %d\n", ray->step_x, ray->step_y);
	printf("side dist = %f | %f\n", ray->side_dist_x, ray->side_dist_y);
	printf("delta dist = %f | %f\n", ray->delta_dist_x, ray->delta_dist_y);
	printf("wall dist = %f\n", ray->wall_dist);
	printf("hit = %d | side = %d | color = %d\n", ray->hit, \
		ray->side, ray->color);
	printf("old pos = %f\n", ray->old_pos_x);
	printf("l_height = %d | d_start = %d | d_end = %d\n", ray->line_height, \
		ray->draw_start, ray->draw_end);
	printf("----------------------------------------------\n");
}

void	texture_init(t_ray *ray)
{
	int	x_col;
	int	y_col;
	int	xy_col;
	int	i;
	int	j;

	i = -1;
	while (++i < T_W)
	{
		j = -1;
		while (++j < T_H)
		{
			x_col = (i * 256 / T_W) ^ (j * 256 / T_H);
			y_col = j * 256 / T_H;
			xy_col = j * 128 / T_H + i * 128 / T_W;
			ray->t[0].t[T_W * j + i] = 65536 * 254 * (i != j && i != T_W - j);
			ray->t[1].t[T_W * j + i] = xy_col + 256 * xy_col + 65536 * xy_col;
			ray->t[2].t[T_W * j + i] = 256 * xy_col + 65536 * xy_col;
			ray->t[3].t[T_W * j + i] = x_col + 256 * x_col + 65536 * x_col;
			ray->t[4].t[T_W * j + i] = 256 * x_col;
			ray->t[5].t[T_W * j + i] = 65536 * 192 * (i % 16 && j % 16);
			ray->t[6].t[T_W * j + i] = 65536 * y_col;
			ray->t[7].t[T_W * j + i] = 128 + 256 * 128 + 65536 * 128;
		}
	}
}

void	draw_screen(t_ray *ray, t_win *win, char **map)
{
	int	x;

	win->img = mlx_new_image(win->mlx, SCREEN_W, SCREEN_H);
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel, \
	&win->size_line, &win->endian);
	win->mini = mlx_new_image(win->mlx, SCREEN_W / 5, SCREEN_H / 5);
	win->addr_mini = mlx_get_data_addr(win->mini, &win->bpp, \
	&win->sl, &win->en);
	texture_init(ray);
	// printf("bug\n");
	x = 0;
	while (x < SCREEN_W)
	{
		win->x = x;
		vars_init(ray, x);
		initial_dist(ray);
		wall_collision(ray, map);
		initial_color(win, ray, map);
		initial_color_2(win, ray);
		x++;
	}
	printf("-----------------------------------------\n");
	ft_verline(win, ray->buffer, 1);
	ft_verline(win, ray->buffer, 0);
	draw_mini_map(ray, win, map);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	mlx_put_image_to_window(win->mlx, win->win, win->mini, \
		SCREEN_W - SCREEN_W / 5, SCREEN_H - SCREEN_H / 5);
	mlx_destroy_image(win->mlx, win->mini);
	mlx_destroy_image(win->mlx, win->img);
}
