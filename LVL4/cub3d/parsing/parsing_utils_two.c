/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:16:45 by atouhami          #+#    #+#             */
/*   Updated: 2022/04/06 14:58:41 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_file_name(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1] && str[i + 2] && str[i + 3]
			&& str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b'
			&& !str[i + 4])
			return (0);
		i++;
	}
	return (-1);
}

int	skip_spaces(char *tmpline)
{
	int	i;

	i = 2;
	while (tmpline[i] == ' ')
		i++;
	return (i);
}

int	assign_floor(t_parsing *parsing, int i)
{
	if (parsing->color_floor != -1 || check_colors(parsing->tmpline))
		return (free_parsing(parsing), printf("Error : duplicate floor color \
		or invalid values\n"), 1);
	parsing->floor_red = ft_atoi(&parsing->tmpline[1]);
	while (parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	if (parsing->tmpline[i])
		i++;
	parsing->floor_green = ft_atoi(parsing->tmpline + i);
	while (parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	if (parsing->tmpline[i])
		i++;
	parsing->floor_blue = ft_atoi(parsing->tmpline + i);
	if (parsing->floor_red > 255 || parsing->floor_green > 255
		|| parsing->floor_blue > 255 || parsing->floor_red < 0
		|| parsing->floor_green < 0 || parsing->floor_blue < 0)
		return (free_parsing(parsing), printf("Error : invalid \
		floor RGB value\n"), 1);
	parsing->color_floor = (parsing->floor_red << 16)
		+ (parsing->floor_green << 8) + parsing->floor_blue;
	parsing->counter += 1;
	return (0);
}

int	assign_ceiling(t_parsing *parsing, int i)
{
	if (parsing->color_ceiling != -1 || check_colors(parsing->tmpline))
		return (free_parsing(parsing), printf("Error : duplicate ceiling color \
		or invalid values\n"), 1);
	parsing->ceiling_red = ft_atoi(&parsing->tmpline[1]);
	while (parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	if (parsing->tmpline[i])
		i++;
	parsing->ceiling_green = ft_atoi(parsing->tmpline + i);
	while (parsing->tmpline[i] && parsing->tmpline[i] != ',')
		i++;
	if (parsing->tmpline[i])
		i++;
	parsing->ceiling_blue = ft_atoi(parsing->tmpline + i);
	if (parsing->ceiling_red > 255 || parsing->ceiling_green > 255
		|| parsing->ceiling_blue > 255 || parsing->ceiling_red < 0
		|| parsing->ceiling_green < 0 || parsing->ceiling_blue < 0)
		return (free_parsing(parsing), printf("Error : Error : invalid \
		ceiling RGB value\n"), 1);
	parsing->color_ceiling = (parsing->ceiling_red << 16)
		+ (parsing->ceiling_green << 8) + parsing->ceiling_blue;
	parsing->counter += 1;
	return (0);
}

int	assign_vars_two(t_parsing *parsing, int i)
{
	if (parsing->tmpline[0] == 'N' && parsing->tmpline[1]
		== 'O' && parsing->tmpline[2] == ' ')
	{
		if (parsing->no != NULL)
			return (free_parsing(parsing), printf("Error : Duplicate NO\n"), 1);
		i = skip_spaces(parsing->tmpline);
		parsing->no = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}
	if (parsing->tmpline[0] == 'S' && parsing->tmpline[1]
		== 'O' && parsing->tmpline[2] == ' ')
	{
		if (parsing->so != NULL)
			return (free_parsing(parsing), printf("Error : Duplicate SO\n"), 1);
		i = skip_spaces(parsing->tmpline);
		parsing->so = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}
	if (assign_vars_three(parsing, 0))
		return (1);
	return (0);
}
