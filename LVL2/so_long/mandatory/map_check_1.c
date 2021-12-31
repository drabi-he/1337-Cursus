/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 10:42:08 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/31 11:22:37 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_get_lines(char *map)
{
	int		fd;
	int		lines;
	char	c;

	fd = open(map, O_RDONLY);
	if (fd < 3)
	{
		printf("file not found or permission denied !!\n");
		exit(0);
	}
	lines = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			lines++;
	}
	close(fd);
	return (++lines);
}

void	ft_check_width(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map[i])
	{
		if ((int)ft_strlen(vars->map[i]) != vars->width)
		{
			printf("all line should have the same width !!\n");
			exit(0);
		}
		i++;
	}
}

void	ft_check_valid(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != 'C' && map[i][j] != 'P'
				&& map[i][j] != 'E')
			{
				printf("invalid component found !!\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void	ft_check_walls(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if ((vars->map[i][j] != '1' && (i == 0 || i == vars->length - 1))
				|| ((vars->map[i][0] != '1'
				|| vars->map[i][vars->width -1] != '1')
				&& (i != 0 || i != vars->length - 1)))
			{
				printf("Walls error !!\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void	ft_gfy_norm(t_vars *vars, int x, int y, int move)
{
	printf("%d moves\n", ++(vars->cp));
	vars->map[x][y] = '0';
	ft_collect_exit(vars, x, y, move);
	mlx_destroy_image(vars->mlx, vars->img_player);
}
