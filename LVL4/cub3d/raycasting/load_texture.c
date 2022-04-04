/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:25:29 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/04 20:45:16 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	load_img(void *mlx, t_texture	*t, char *filename)
{
	int	w;
	int	h;

	t->img = mlx_xpm_file_to_image(mlx, filename, &w, &h);
	t->addr = mlx_get_data_addr(t->img, &t->bpp, &t->sl, &t->en);
}

void	load_texture(t_win *win, t_ray *ray)
{
	load_img(win->mlx, &ray->t[0], "./pics/eagle.xpm");
	load_img(win->mlx, &ray->t[1], "./pics/redbrick.xpm");
	load_img(win->mlx, &ray->t[2], "./pics/purplestone.xpm");
	load_img(win->mlx, &ray->t[3], "./pics/greystone.xpm");
	load_img(win->mlx, &ray->t[4], "./pics/bluestone.xpm");
	load_img(win->mlx, &ray->t[5], "./pics/mossy.xpm");
	load_img(win->mlx, &ray->t[6], "./pics/wood.xpm");
	load_img(win->mlx, &ray->t[7], "./pics/colorstone.xpm");
}
