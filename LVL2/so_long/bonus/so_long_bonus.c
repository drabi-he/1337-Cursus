/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:54:10 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/03 13:10:34 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	ft_close(void)
{
	exit(0);
}

void	ft_gameplay(t_vars *vars)
{
	ft_vars_init(vars);
	ft_fill_window(*vars);
	mlx_key_hook(vars->win, ft_key_events, vars);
	mlx_hook(vars->win, 17, 0, ft_close, NULL);
	mlx_loop_hook(vars->mlx, anim, vars);
	mlx_loop(vars->mlx);
}

int	main(int ac, char *av[])
{
	t_vars	vars;
	
	ft_check_args(ac, av);
	ft_check_valid_map(&vars, av[1]);
	ft_gameplay(&vars);
}
