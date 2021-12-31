/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 10:43:33 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/31 11:24:20 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

static void	ft_process_map(t_vars *vars, char *path)
{
	int	fd;
	int	length;
	int	i;

	length = ft_get_lines(path);
	vars->map = (char **)malloc((length + 1) * sizeof(char *));
	fd = open(path, O_RDONLY);
	if (fd < 3)
	{
		printf("file not found or permission denied !!\n");
		exit(0);
	}
	i = 0;
	while (i < length)
	{
		vars->map[i] = get_next_line(fd);
		i++;
	}
	vars->length = length;
	vars->width = ft_strlen(vars->map[0]);
	vars->map[i] = 0;
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
