/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:36:19 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/31 11:37:43 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	ft_mini_init(int *a, int *b, int *c, int *d)
{
	*a = 1;
	*b = 0;
	*c = 0;
	*d = 0;
}

static void	ft_mini_check(int a, int b, int c)
{
	if (a == 0 || b == 0 || c != 1)
	{
		printf("components error");
		printf("(1 player | >= 1 collectible | >= 1 Exit) !!\n");
		exit(0);
	}
}

static void	ft_check_components(t_vars *vars)
{
	int	i;
	int	j;
	int	is_exit;
	int	is_collect;
	int	is_player;

	ft_mini_init(&i, &is_exit, &is_collect, &is_player);
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'E')
				is_exit = 1;
			if (vars->map[i][j] == 'P')
				is_player++;
			if (vars->map[i][j] == 'C')
				is_collect++;
			j++;
		}
		i++;
	}
	ft_mini_check(is_exit, is_collect, is_player);
	vars->collect = is_collect;
	vars->exit = 0;
}

void	ft_check_args(int ac, char **av)
{
	if (ac == 1)
	{
		printf("please entre map path !!\n");
		exit(0);
	}
	else if (ac > 2)
	{
		printf("too many arguments !!\n");
		exit(0);
	}
	else
	{
		if (ft_strcmp(".ber", ft_strstr(av[1], ".ber\0")))
		{
			printf("map format error !!\n");
			exit(0);
		}
	}
}

void	ft_check_valid_map(t_vars *vars, char *path)
{
	ft_process_map(vars, path);
	ft_check_width(vars);
	if (vars->length == vars->width)
	{
		printf("map should be rectangular !!\n");
		exit(0);
	}
	ft_check_valid(vars->map);
	ft_check_walls(vars);
	ft_check_components(vars);
}