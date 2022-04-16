/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 00:43:52 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/08 23:46:38 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	pixel_put_mini(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr_mini + (x * (win->bpp / 8) + y * win->sl);
	*(int *)dst = color;
}

static void	scale_mini_2(t_win *win, float x, float y, int color)
{
	int	s;
	int	e;

	x -= win->info.start[1];
	y -= win->info.start[0];
	x *= 10;
	y *= 10;
	x -= 5;
	y -= 5;
	s = x + 10;
	e = y + 10;
	while (y < e)
	{
		while (x < s)
			pixel_put_mini(win, x++, y, color);
		x -= 10;
		y++;
	}
}

int	scale_mini(t_win *win, float x, float y, int color)
{
	int	s;
	int	e;

	x -= win->info.start[1];
	y -= win->info.start[0];
	x *= 10;
	y *= 10;
	s = x + 10;
	e = y + 10;
	while (y < e - 1)
	{
		while (x < s - 1)
			pixel_put_mini(win, x++, y, color);
		x -= 9;
		y++;
	}
	return (1);
}

int	draw_mini_map(t_ray *ray, t_win *win, char **map)
{
	int	i;
	int	j;

	i = ray->pos[X] - win->info.height / 2;
	if (i < 0)
		i = 0;
	win->info.start[0] = i;
	win->info.end[0] = i + win->info.height;
	while (map[i] && i < win->info.end[0])
	{
		j = ray->pos[Y] - win->info.width / 2;
		if (j < 0)
			j = 0;
		win->info.start[1] = j;
		win->info.end[1] = j + win->info.width;
		while (map[i][j] && j < win->info.end[1])
		{
			choose_color(win, (float)j, (float)i, map[i][j]);
			j++;
		}
		i++;
	}
	scale_mini_2(win, ray->pos[Y], ray->pos[X], 0x00FFFF);
	return (1);
}

unsigned int	get_color(t_texture *t, int x, int y)
{
	char	*ptr;
	int		pixel;

	pixel = y * t->sl + x * 4;
	ptr = t->addr + pixel;
	return ((((unsigned char)ptr[2]) << 16)
		+ (((unsigned char)ptr[1]) << 8) + ((unsigned char)ptr[0]));
}
