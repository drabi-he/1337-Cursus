/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 00:02:30 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/09 13:28:58 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (x * (win->bits_per_pixel / 8) + y * win->size_line);
	*(int *)dst = color;
}

int	ft_verline(t_win *win, unsigned int **buffer, int mode)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SCREEN_H)
	{
		j = -1;
		while (++j < SCREEN_W)
		{
			if (mode)
				pixel_put(win, j, i, buffer[i][j]);
			else
				buffer[i][j] = 0;
		}
	}
	return (1);
}

void	dda_and_draw(t_ray *ray, t_win *win, char **map, int x)
{
	vars_init(ray, x);
	initial_dist(ray);
	wall_collision(ray, map);
	initial_color(ray);
	initial_color_2(win, ray);
}

void	print_ray(t_ray *ray)
{
	printf("pos = %f | %f\n", ray->pos[X], ray->pos[Y]);
	printf("dir = %f | %f\n", ray->dir[X], ray->dir[Y]);
	printf("plane = %f | %f\n", ray->plane[X], ray->plane[Y]);
	printf("camera = %f\n", ray->camera);
	printf("ray dir = %f | %f\n", ray->ray_dir[X], ray->ray_dir[Y]);
	printf("map = %d | %d\n", ray->map[X], ray->map[Y]);
	printf("step = %d | %d\n", ray->step[X], ray->step[Y]);
	printf("side dist = %f | %f\n", ray->side_dist[X], ray->side_dist[Y]);
	printf("delta dist = %f | %f\n", ray->delta_dist[X], ray->delta_dist[Y]);
	printf("wall dist = %f\n", ray->wall_dist);
	printf("hit = %d | side = %d | color = %d\n", ray->hit, \
		ray->side, ray->color);
	printf("old pos = %f\n", ray->old_pos_x);
	printf("l_height = %d | d_start = %d | d_end = %d\n", ray->line_height, \
		ray->draw[0], ray->draw[1]);
	printf("----------------------------------------------\n");
}

void	draw_screen(t_ray *ray, t_win *win, char **map, int mode)
{
	int	x;

	win->img = mlx_new_image(win->mlx, SCREEN_W, SCREEN_H);
	win->addr = mlx_get_data_addr(win->img, &win->bits_per_pixel, \
	&win->size_line, &win->endian);
	if (mode == BONUS)
	{
		win->mini = mlx_new_image(win->mlx, SCREEN_W / 5, SCREEN_H / 5);
		win->addr_mini = mlx_get_data_addr(win->mini, &win->bpp, \
		&win->sl, &win->en);
	}
	x = -1;
	while (++x < SCREEN_W)
	{
		win->x = x;
		dda_and_draw(ray, win, map, x);
	}
	(mode == BONUS && sprites(ray, map));
	(ft_verline(win, ray->buffer, 1) && ft_verline(win, ray->buffer, 0));
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	(mode == BONUS && draw_mini_map(ray, win, map) \
		&& mlx_put_image_to_window(win->mlx, win->win, win->mini, \
			SCREEN_W - SCREEN_W / 5, SCREEN_H - SCREEN_H / 5) \
		&& mlx_destroy_image(win->mlx, win->mini));
	mlx_destroy_image(win->mlx, win->img);
}
