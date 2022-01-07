/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_anim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:50:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/07 15:56:04 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_move2(t_vars *vars, int i, int j, int move)
{
	if (move == 0)
	{
		vars->map[i][j] = '0';
		vars->map[i][j - 1] = 'F';
	}
	if (move == 1)
	{
		vars->map[i][j] = '0';
		vars->map[i][j + 1] = 'F';
	}
	if (move == 2)
	{
		vars->map[i][j] = '0';
		vars->map[i - 1][j] = 'F';
	}
	if (move == 3)
	{
		vars->map[i][j] = '0';
		vars->map[i + 1][j] = 'F';
	}
}

static int	ft_enemy_valid(t_vars *vars, int i, int j)
{
	if (vars->map[i][j] == '0')
		return (1);
	if (vars->map[i][j] == 'P')
	{
		mlx_destroy_image(vars->mlx, vars->img_player);
		mlx_clear_window(vars->mlx, vars->win);
		vars->img_player = mlx_xpm_file_to_image(vars->mlx,
				"./assests/dead.xpm", &i, &j);
		vars->game_over = 1;
		ft_fill_window(*vars);
		printf("you lose !!\n");
		return (0);
	}
	return (0);
}

static void	ft_move_enemy(t_vars *vars, int i, int j)
{
	int		r;
	char	*moves;

	r = rand() % 4;
	if (r == 0 && ft_enemy_valid(vars, i, j - 1))
		ft_move2(vars, i, j, r);
	if (r == 1 && ft_enemy_valid(vars, i, j + 1))
		ft_move2(vars, i, j, r);
	if (r == 2 && ft_enemy_valid(vars, i - 1, j))
		ft_move2(vars, i, j, r);
	if (r == 3 && ft_enemy_valid(vars, i + 1, j))
		ft_move2(vars, i, j, r);
	ft_fill_window(*vars);
	moves = ft_itoa(vars->cp);
	mlx_string_put(vars->mlx, vars->win, 10, 10, 0xffffffff, moves);
	free(moves);
}

void	ft_anim_enemy(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'F')
				ft_move_enemy(vars, i, j);
			j++;
		}
		i++;
	}
}
