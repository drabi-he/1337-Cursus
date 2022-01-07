/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:38:49 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/07 14:46:41 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_collect_img(t_vars *vars, int *cord)
{
	vars->img_collect[0] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/box1.xpm", &cord[0], &cord[1]);
	vars->img_collect[1] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/box2.xpm", &cord[0], &cord[1]);
	vars->img_collect[2] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/box3.xpm", &cord[0], &cord[1]);
	vars->img_collect[3] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/box4.xpm", &cord[0], &cord[1]);
	vars->img_collect[4] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/box5.xpm", &cord[0], &cord[1]);
	vars->img_collect[5] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/box6.xpm", &cord[0], &cord[1]);
	vars->img_collect[6] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/box7.xpm", &cord[0], &cord[1]);
	vars->img_collect[7] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/box8.xpm", &cord[0], &cord[1]);
}

static void	ft_door_img(t_vars *vars, int *cord)
{
	vars->img_exit[0] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/door1.xpm", &cord[0], &cord[1]);
	vars->img_exit[1] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/door2.xpm", &cord[0], &cord[1]);
	vars->img_exit[2] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/door3.xpm", &cord[0], &cord[1]);
	vars->img_exit[3] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/door4.xpm", &cord[0], &cord[1]);
	vars->img_exit[4] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/door5.xpm", &cord[0], &cord[1]);
	vars->img_exit[5] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/door6.xpm", &cord[0], &cord[1]);
}

void	ft_vars_init(t_vars *vars)
{
	int	cord[2];

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx,
			50 * vars->width, 50 * vars->length, "So Long");
	vars->cp = 0;
	vars->img_wall = mlx_xpm_file_to_image(vars->mlx,
			"./assests/wall.xpm", &cord[0], &cord[1]);
	vars->img_floor = mlx_xpm_file_to_image(vars->mlx,
			"./assests/floor.xpm", &cord[0], &cord[1]);
	vars->img_player = mlx_xpm_file_to_image(vars->mlx,
			"./assests/playerR.xpm", &cord[0], &cord[1]);
	vars->img_enemy = mlx_xpm_file_to_image(vars->mlx,
			"./assests/enemy.xpm", &cord[0], &cord[1]);
	ft_collect_img(vars, cord);
	ft_door_img(vars, cord);
	vars->game_over = 0;
}

static void	ft_choose_img(t_vars vars, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(vars.mlx,
			vars.win, vars.img_wall, 50 * x, 50 * y);
	else
	{
		mlx_put_image_to_window(vars.mlx,
			vars.win, vars.img_floor, 50 * x, 50 * y);
		if (c == 'P')
			mlx_put_image_to_window(vars.mlx,
				vars.win, vars.img_player, 50 * x, 50 * y);
		if (c == 'C')
			mlx_put_image_to_window(vars.mlx,
				vars.win, vars.img_collect[0], 50 * x, 50 * y);
		if (c == 'E' && (vars.collect || vars.exit))
			mlx_put_image_to_window(vars.mlx,
				vars.win, vars.img_exit[0], 50 * x, 50 * y);
		if (c == 'E' && !vars.exit && !vars.collect)
			mlx_put_image_to_window(vars.mlx,
				vars.win, vars.img_exit[5], 50 * x, 50 * y);
		if (c == 'F')
			mlx_put_image_to_window(vars.mlx,
				vars.win, vars.img_enemy, 50 * x, 50 * y);
	}
}

void	ft_fill_window(t_vars vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars.map[i])
	{
		j = 0;
		while (vars.map[i][j])
		{
			ft_choose_img(vars, vars.map[i][j], j, i);
			j++;
		}
		i++;
	}
}
