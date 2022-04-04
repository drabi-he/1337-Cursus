/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:06:45 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/02 14:47:43 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_player(char **map, t_win *win, t_ray *ray)
{
	float	x;
	float	y;

	x = ray->pos_x - win->info.i_start;
	y = ray->pos_y - win->info.j_start;
	x *= 5;
	y *= 5;
	while (map[(int)(x / 5)][(int)(y / 5)] < '1' \
		|| map[(int)(x / 5)][(int)(y / 5)] > '9')
	{
		x += ray->dir_x;
		y += ray->dir_y;
		pixel_put_mini(win, y - ray->dir_y, x - ray->dir_x, RED);
	}
}

void	scale_mini_2(t_win *win, float x, float y, int color)
{
	int	s;
	int	e;

	x -= win->info.j_start;
	y -= win->info.i_start;
	x *= 5;
	y *= 5;
	x -= 2.5;
	y -= 2.5;
	s = x + 5;
	e = y + 5;
	while (y < e)
	{
		while (x < s)
			pixel_put_mini(win, x++, y, color);
		x -= 5;
		y++;
	}
}

void	scale_mini(t_win *win, float x, float y, int color)
{
	int	s;
	int	e;

	x -= win->info.j_start;
	y -= win->info.i_start;
	x *= 5;
	y *= 5;
	s = x + 5;
	e = y + 5;
	while (y < e)
	{
		while (x < s)
			pixel_put_mini(win, x++, y, color);
		x -= 5;
		y++;
	}
}

void	draw_mini_map(t_ray *ray, t_win *win, char **map)
{
	int	i;
	int	j;

	i = ray->pos_x - win->info.height;
	if (i < 0)
		i = 0;
	win->info.i_start = i;
	win->info.i_end = i + 2 * win->info.height;
	while (map[i] && i < win->info.i_end)
	{
		j = ray->pos_y - win->info.width;
		if (j < 0)
			j = 0;
		win->info.j_start = j;
		win->info.j_end = j + 2 * win->info.width;
		while (map[i][j] && j < win->info.j_end)
		{
			if (map[i][j] > '0' && map[i][j] < '9')
				scale_mini(win, (float)j, (float)i, WHITE);
			j++;
		}
		i++;
	}
	scale_mini_2(win, ray->pos_y, ray->pos_x, GREEN);
}
