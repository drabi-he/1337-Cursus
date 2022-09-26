/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:40:59 by hdrabi            #+#    #+#             */
/*   Updated: 2022/09/15 11:58:42 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	texture_init(void *mlx, t_ray *ray, t_data data)
{
	ray->ceiling = data.ceiling;
	ray->floor = data.floor;
	load_img(mlx, &ray->t[0], data.no);
	load_img(mlx, &ray->t[1], data.so);
	load_img(mlx, &ray->t[2], data.ea);
	load_img(mlx, &ray->t[3], data.we);
	load_img(mlx, &ray->t[4], "./assets/demon1.xpm");
	load_img(mlx, &ray->t[5], "./assets/demon2.xpm");
	load_img(mlx, &ray->t[6], "./assets/demon3.xpm");
	load_img(mlx, &ray->t[7], "./assets/demon4.xpm");
	load_img(mlx, &ray->t[8], "./assets/demon5.xpm");
	load_img(mlx, &ray->t[9], "./assets/demon6.xpm");
	load_img(mlx, &ray->t[10], "./assets/demon7.xpm");
	load_img(mlx, &ray->t[11], "./assets/demon8.xpm");
	load_img(mlx, &ray->t[12], "./assets/demon9.xpm");
	load_img(mlx, &ray->t[13], "./assets/demon10.xpm");
	load_img(mlx, &ray->t[14], "./assets/demon11.xpm");
	load_img(mlx, &ray->t[15], "./assets/door.xpm");
	load_img(mlx, &ray->t[16], "./assets/teemo.xpm");
	ray->sprite = malloc(ray->amount * sizeof(t_sprite));
	(!ray->sprite && ft_error("Error: allocation failed\n", 1));
	ray->anime = 0;
}

static void	init_dir(char c, t_ray **ray)
{
	if (c == 'N' || c == 'S')
	{
		ray[0]->dir[X] = 1;
		ray[0]->dir[Y] = 0;
		ray[0]->plane[X] = 0;
		ray[0]->plane[Y] = -0.66;
		if (c == 'N')
		{
			ray[0]->dir[X] = -1;
			ray[0]->plane[Y] = 0.66 ;
		}
	}
	if (c == 'E' || c == 'W')
	{
		ray[0]->dir[X] = 0;
		ray[0]->dir[Y] = 1;
		ray[0]->plane[X] = 0.66;
		ray[0]->plane[Y] = 0;
		if (c == 'W')
		{
			ray[0]->dir[Y] = -1;
			ray[0]->plane[X] = -0.66;
		}
	}
}

static void	init_player(char	**map, float *x, float *y, char *c)
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
				*c = map[i][j];
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
}

static void	ray_init(t_ray *ray, t_data data, int mode, char **map)
{
	char	c;
	int		i;

	init_player(data.map, &ray->pos[X], &ray->pos[Y], &c);
	init_dir(c, &ray);
	ray->buffer = malloc(SCREEN_H * sizeof(unsigned int *));
	(!ray->buffer && ft_error("Error: allocation failed\n", 1));
	i = -1;
	while (++i < SCREEN_H)
	{
		ray->buffer[i] = malloc(SCREEN_W * sizeof(unsigned int));
		(!ray->buffer[i] && ft_error("Error: allocation failed\n", 1));
	}
	if (mode == BONUS)
	{
		ray->amount = count_sprites(map);
		ray->z_buffer = malloc(SCREEN_W * sizeof(float));
		(!ray->z_buffer && ft_error("Error: allocation failed\n", 1));
		ray->sprit_order = malloc(ray->amount * sizeof(int));
		(!ray->sprit_order && ft_error("Error: allocation failed\n", 1));
		ray->sprit_distance = malloc(ray->amount * sizeof(float));
		(!ray->sprit_distance && ft_error("Error: allocation failed\n", 1));
	}
}

void	init_all(t_all *all, t_data data, int mode)
{
	t_ray	ray;
	t_win	win;

	all->map = data.map;
	ray_init(&ray, data, mode, all->map);
	win.mode = mode;
	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, SCREEN_W, SCREEN_H, "cub3D");
	win.info.height = SCREEN_H / 50;
	win.info.width = SCREEN_W / 50;
	texture_init(win.mlx, &ray, data);
	draw_screen(&ray, &win, all->map, mode);
	all->ray = &ray;
	all->win = &win;
	mlx_hook(win.win, 2, (1L << 0), key_press, all);
	mlx_hook(win.win, 3, (1L << 1), key_release, all);
	mlx_hook(win.win, 17, 0, &ft_close, NULL);
	mlx_loop_hook(win.mlx, smooth_move, all);
	if (mode == BONUS)
		mlx_hook(win.win, 6, (1L << 6), ft_move, all);
	mlx_loop(win.mlx);
}
