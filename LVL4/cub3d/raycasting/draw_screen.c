/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:10:30 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/06 01:52:58 by hdrabi           ###   ########.fr       */
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

unsigned int	get_color(t_texture *t, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * t->sl + x * 4;
	ptr = t->addr + pixel;
	if (t->en == 0)
		return ((((unsigned char)ptr[2]) << 16)
			+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
	return ((((unsigned char)ptr[0]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[2]));
}

void	initial_color_2(t_win *win, t_ray *ray)
{
	int	i;

	i = 0;
	while (i < ray->draw_start)
		ray->buffer[i++][win->x] = 0x90e0ef;
	while (i < ray->draw_end)
	{
		ray->tex_y = (int)ray->tex_pos & (T_H - 1);
		ray->tex_pos += ray->step;
		ray->color = get_color(&ray->t[ray->tex_num], ray->tex_x, ray->tex_y);
		if (ray->side == 1)
			ray->color = (ray->color >> 1) & 8355711;
		ray->buffer[i][win->x] = ray->color;
		i++;
	}
	while (i < SCREEN_H)
		ray->buffer[i++][win->x] = 0x99d98c;
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

void	draw_screen(t_ray *ray, t_win *win, char **map)
{
	int	x;

	win->img = mlx_new_image(win->mlx, SCREEN_W, SCREEN_H);
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel, \
	&win->size_line, &win->endian);
	win->mini = mlx_new_image(win->mlx, SCREEN_W / 5, SCREEN_H / 5);
	win->addr_mini = mlx_get_data_addr(win->mini, &win->bpp, \
	&win->sl, &win->en);
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
	ft_verline(win, ray->buffer, 1);
	ft_verline(win, ray->buffer, 0);
	draw_mini_map(ray, win, map);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	mlx_put_image_to_window(win->mlx, win->win, win->mini, \
		SCREEN_W - SCREEN_W / 5, SCREEN_H - SCREEN_H / 5);
	mlx_destroy_image(win->mlx, win->mini);
	mlx_destroy_image(win->mlx, win->img);
}
