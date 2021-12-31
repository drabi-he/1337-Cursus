/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:34:17 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/31 11:34:36 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	ft_get_lines(char *map)
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
				&& map[i][j] != 'E' && map[i][j] != 'F')
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
				|| ((vars->map[i][0] != '1' || vars->map[i][vars->width -1] != '1')
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

void	ft_process_map(t_vars *vars, char *path)
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