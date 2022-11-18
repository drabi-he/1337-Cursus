/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 10:45:39 by hdrabi            #+#    #+#             */
/*   Updated: 2022/11/16 14:54:55 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_vars_init(t_vars *vars)
{
	int	cord[2];

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 50 * vars->width,
			50 * vars->length, "So Long");
	vars->cp = 0;
	vars->img_wall = mlx_xpm_file_to_image(vars->mlx,
			"./assests/wall.xpm", &cord[0], &cord[1]);
	vars->img_floor = mlx_xpm_file_to_image(vars->mlx,
			"./assests/floor.xpm", &cord[0], &cord[1]);
	vars->img_player = mlx_xpm_file_to_image(vars->mlx,
			"./assests/playerR.xpm", &cord[0], &cord[1]);
	vars->img_collect = mlx_xpm_file_to_image(vars->mlx,
			"./assests/boxM.xpm", &cord[0], &cord[1]);
	vars->img_exit[0] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/door1.xpm", &cord[0], &cord[1]);
	vars->img_exit[1] = mlx_xpm_file_to_image(vars->mlx,
			"./assests/door6.xpm", &cord[0], &cord[1]);
}

void	ft_choose_img(t_vars vars, char c, int x, int y)
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
				vars.win, vars.img_collect, 50 * x, 50 * y);
		if (c == 'E' && vars.exit == 0 && vars.collect)
			mlx_put_image_to_window(vars.mlx,
				vars.win, vars.img_exit[0], 50 * x, 50 * y);
		if (c == 'E' && !vars.collect)
			mlx_put_image_to_window(vars.mlx,
				vars.win, vars.img_exit[1], 50 * x, 50 * y);
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

void	get_player_pos(char **map, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*x = i;
				*y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	ft_valid_move(char **map, int collect, int x, int y)
{
	if (map[x][y] == '0' || map[x][y] == 'C' || (map[x][y] == 'E' && !collect))
		return (1);
	return (0);
}
