/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:40:09 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/07 13:35:55 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

int	ft_valid_move(t_vars *vars, int x, int y)
{
	if (vars->map[x][y] == '0' || vars->map[x][y] == 'C'
		|| (vars->map[x][y] == 'E' && !vars->collect) || vars->map[x][y] == 'F')
	{
		if (vars->game_over == 0)
			++vars->cp;
		return (1);
	}
	return (0);
}

void	ft_gameover(t_vars *vars)
{
	if (vars->game_over == 1)
	{
		mlx_clear_window(vars->mlx, vars->win);
		ft_fill_window(*vars);
		mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
}

void	ft_dead(t_vars *vars, char c)
{
	int	x;
	int	y;

	ft_gameover(vars);
	if (c == 'F')
	{
		mlx_destroy_image(vars->mlx, vars->img_player);
		mlx_clear_window(vars->mlx, vars->win);
		vars->img_player = mlx_xpm_file_to_image(vars->mlx,
				"./assests/dead.xpm", &x, &y);
		vars->game_over = 1;
		ft_fill_window(*vars);
		printf("you lose !!\n");
	}
}

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
	{
		vars->collect--;
		if (vars->collect == 0)
		vars->exit = 1;
	}
	if (vars->map[x][y] == 'E')
	{
		sleep(1);
		printf("you won!!\n");
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	ft_dead(vars, vars->map[x][y]);
}
