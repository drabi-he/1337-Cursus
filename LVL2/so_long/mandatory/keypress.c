/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 10:46:47 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/12 13:07:31 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_collect_exit(t_vars *vars, int x, int y, int move)
{
	if (move == 1)
		y++;
	if (move == 2)
		y--;
	if (move == 3)
		x--;
	if (move == 4)
		x++;
	if (vars->map[x][y] == 'C')
		vars->collect--;
	if (vars->collect == 0)
		vars->exit = 1;
	if (vars->map[x][y] == 'E')
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
}

static void	ft_move_player(t_vars *vars, int x, int y, int move)
{
	ft_gfy_norm(vars, x, y, move);
	if (move == 1)
	{
		vars->map[x][++y] = 'P';
		vars->img_player = mlx_xpm_file_to_image(vars->mlx,
				"./assests/playerR.xpm", &x, &y);
	}
	if (move == 2)
	{
		vars->map[x][--y] = 'P';
		vars->img_player = mlx_xpm_file_to_image(vars->mlx,
				"./assests/playerL.xpm", &x, &y);
	}
	if (move == 3)
	{
		vars->map[--x][y] = 'P';
		vars->img_player = mlx_xpm_file_to_image(vars->mlx,
				"./assests/playerU.xpm", &x, &y);
	}
	if (move == 4)
	{
		vars->map[++x][y] = 'P';
		vars->img_player = mlx_xpm_file_to_image(vars->mlx,
				"./assests/playerD.xpm", &x, &y);
	}
}

static void	ft_movments(t_vars *vars, int keypress, int x, int y)
{
	if ((keypress == 2 || keypress == 124)
		&& ft_valid_move(vars->map, vars->collect, x, y + 1))
		ft_move_player(vars, x, y, 1);
	if ((keypress == 0 || keypress == 123)
		&& ft_valid_move(vars->map, vars->collect, x, y - 1))
		ft_move_player(vars, x, y, 2);
	if ((keypress == 13 || keypress == 126)
		&& ft_valid_move(vars->map, vars->collect, x - 1, y))
		ft_move_player(vars, x, y, 3);
	if ((keypress == 1 || keypress == 125)
		&& ft_valid_move(vars->map, vars->collect, x + 1, y))
		ft_move_player(vars, x, y, 4);
	mlx_clear_window(vars->mlx, vars->win);
	ft_fill_window(*vars);
}

int	ft_key_events(int keypress, t_vars *vars)
{
	int	x;
	int	y;

	get_player_pos(vars->map, &x, &y);
	if (keypress == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	ft_movments(vars, keypress, x, y);
	return (0);
}

int	ft_close(void)
{
	exit(0);
}
