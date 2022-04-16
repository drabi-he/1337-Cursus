/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 13:53:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/16 00:45:59 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_swap(t_pair	**sprites, int amount)
{
	int		tmp1;
	float	tmp2;
	int		i;
	int		j;

	i = -1;
	while (++i < amount)
	{
		j = i - 1;
		while (++j < amount)
		{
			if (sprites[0][i].first > sprites[0][j].first)
			{
				tmp1 = sprites[0][i].first;
				sprites[0][i].first = sprites[0][j].first;
				sprites[0][j].first = tmp1;
				tmp2 = sprites[0][i].second;
				sprites[0][i].second = sprites[0][j].second;
				sprites[0][j].second = tmp2;
			}
		}
	}
}

void	sort_sprites(int *order, float *dist, int amount)
{
	t_pair	*sprites;
	int		i;

	i = -1;
	sprites = malloc(amount * sizeof(t_pair));
	if (!sprites)
		ft_error("Error: failed allocation\n", 1);
	while (++i < amount)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	ft_swap(&sprites, amount);
	i = -1;
	while (++i < amount)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
}

void	sprit_dda_1(t_ray *ray, int i)
{
	ray->spr[X] = ray->sprite[ray->sprit_order[i]].x - ray->pos[X];
	ray->spr[Y] = ray->sprite[ray->sprit_order[i]].y - ray->pos[Y];
	ray->inv_det = 1.0 / (ray->plane[X] * ray->dir[Y] \
			- ray->dir[X] * ray->plane[Y]);
	ray->transform[X] = ray->inv_det * (ray->dir[Y] * ray->spr[X] \
			- ray->dir[X] * ray->spr[Y]);
	ray->transform[Y] = ray->inv_det * (-ray->plane[Y] * ray->spr[X] \
			+ ray->plane[X] * ray->spr[Y]);
	ray->spr_screen = (int)((SCREEN_W / 2) * (1 + ray->transform[X] \
			/ ray->transform[Y]));
	ray->move_screen = (int)(V_MOVE / ray->transform[Y]);
	ray->spr_h = abs((int)(SCREEN_H / ray->transform[Y])) / V_DIV;
	ray->draw_y[0] = -ray->spr_h / 2 + SCREEN_H / 2 + ray->move_screen;
	if (ray->draw_y[0] < 0)
		ray->draw_y[0] = 0;
	ray->draw_y[1] = ray->spr_h / 2 + SCREEN_H / 2 + ray->move_screen;
	if (ray->draw_y[1] >= SCREEN_H)
		ray->draw_y[1] = SCREEN_H - 1;
	ray->spr_w = abs((int)(SCREEN_H / ray->transform[Y])) / U_DIV;
	ray->draw_x[0] = -ray->spr_w / 2 + ray->spr_screen;
	if (ray->draw_x[0] < 0)
		ray->draw_x[0] = 0;
	ray->draw_x[1] = ray->spr_h / 2 + ray->spr_screen;
	if (ray->draw_x[1] > SCREEN_W)
		ray->draw_x[1] = SCREEN_W;
}

void	sprit_dda_2(t_ray *ray, int i, int x)
{
	int	y;
	int	d;

	ray->s = ray->draw_x[0] - 1;
	while (++ray->s < ray->draw_x[1])
	{
		ray->tex[X] = (int)(256 * (ray->s - (-ray->spr_w / 2 + \
		ray->spr_screen)) * T_W / ray->spr_w) / 256;
		if (ray->transform[Y] > 0 && ray->transform[Y] < ray->z_buffer[ray->s])
		{
			y = ray->draw_y[0] - 1;
			while (++y < ray->draw_y[1])
			{
				d = (y - ray->move_screen) * 256 - SCREEN_H * 128 \
					+ ray->spr_h * 128;
				ray->tex[Y] = ((d * T_H) / ray->spr_h) / 256;
				if (ray->sprite[ray->sprit_order[i]].texture == 16)
					x = 0;
				ray->color = get_color(&ray->t[ray->sprite[ray->\
				sprit_order[i]].texture + x], ray->tex[X], ray->tex[Y]);
				if ((ray->color & 0x00FFFFFF) != 0)
					ray->buffer[y][ray->s] = ray->color;
			}
		}
	}
}

int	sprites(t_ray *ray, char **map)
{
	int	i;

	i = -1;
	init_sprit_locations(&ray->sprite, map);
	while (++i < ray->amount)
	{
		ray->sprit_order[i] = i;
		ray->sprit_distance[i] = (float)(pow(ray->pos[X] - ray->sprite[i].x, 2) \
		- pow(ray->pos[Y] - ray->sprite[i].y, 2));
	}
	sort_sprites(ray->sprit_order, ray->sprit_distance, ray->amount);
	i = -1;
	while (++i < ray->amount)
	{
		sprit_dda_1(ray, i);
		sprit_dda_2(ray, i, ray->anime);
	}
	return (1);
}
