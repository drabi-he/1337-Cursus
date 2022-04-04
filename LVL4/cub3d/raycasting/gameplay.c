/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:50:48 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/04 20:30:16 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	gameplay(t_all *all)
{
	ray_init(&all->ray, all->map);
	all->win.mlx = mlx_init();
	all->win.win = mlx_new_window(all->win.mlx, SCREEN_W, SCREEN_H, "cub3D");
	all->win.info.height = SCREEN_H / 50;
	all->win.info.width = SCREEN_W / 50;
	load_texture(&all->win, &all->ray);
	draw_screen(&all->ray, &all->win, all->map);
	mlx_hook(all->win.win, 2, (1L << 0), key_press, &all->win);
	mlx_loop(all->win.mlx);
}
