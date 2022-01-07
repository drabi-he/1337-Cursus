/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:51:45 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/07 15:08:03 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_gfy_norm(t_vars *vars, int move)
{
	int	x;
	int	y;

	if (move == 1)
			vars->img_player = mlx_xpm_file_to_image(vars->mlx,
				"./assests/playerR.xpm", &x, &y);
	if (move == 2)
			vars->img_player = mlx_xpm_file_to_image(vars->mlx,
				"./assests/playerL.xpm", &x, &y);
	if (move == 3)
			vars->img_player = mlx_xpm_file_to_image(vars->mlx,
				"./assests/playerU.xpm", &x, &y);
	if (move == 4)
			vars->img_player = mlx_xpm_file_to_image(vars->mlx,
				"./assests/playerD.xpm", &x, &y);
}

static void	ft_player_img(t_vars *vars, int x, int y, int move)
{
	if (vars->game_over == 1)
		return ;
	if (move == 1)
		vars->map[x][++y] = 'P';
	if (move == 2)
		vars->map[x][--y] = 'P';
	if (move == 3)
		vars->map[--x][y] = 'P';
	if (move == 4)
		vars->map[++x][y] = 'P';
	ft_gfy_norm(vars, move);
}

static void	ft_move_player(t_vars *vars, int x, int y, int move)
{
	ft_collect_exit(vars, x, y, move);
	if (vars->game_over == 1)
		return ;
	vars->map[x][y] = '0';
	mlx_destroy_image(vars->mlx, vars->img_player);
	ft_player_img(vars, x, y, move);
}

static void	ft_movments(t_vars *vars, int keypress, int x, int y)
{
	char	*moves;

	if ((keypress == 2 || keypress == 124) && ft_valid_move(vars, x, y + 1))
		ft_move_player(vars, x, y, 1);
	if ((keypress == 0 || keypress == 123) && ft_valid_move(vars, x, y - 1))
		ft_move_player(vars, x, y, 2);
	if ((keypress == 13 || keypress == 126) && ft_valid_move(vars, x - 1, y))
		ft_move_player(vars, x, y, 3);
	if ((keypress == 1 || keypress == 125) && ft_valid_move(vars, x + 1, y))
		ft_move_player(vars, x, y, 4);
	mlx_clear_window(vars->mlx, vars->win);
	ft_fill_window(*vars);
	moves = ft_itoa(vars->cp);
	mlx_string_put(vars->mlx, vars->win, 10, 10, 0xffffffff, moves);
	free(moves);
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
