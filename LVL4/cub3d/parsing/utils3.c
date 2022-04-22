/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 14:31:04 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/22 13:53:25 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_horizontal(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
		{
			while (j < data->width && data->map[i][j] == ' ')
				j++;
			if (!data->map[i][j])
				break ;
			if (data->map[i][j] != '1')
				ft_error("Error: map not enclosed vertically\n", 1);
			else
			{
				while (j < data->width && data->map[i][j] != ' ')
					j++;
				if (data->map[i][j - 1] != '1')
					ft_error("Error: map not enclosed vertically\n", 1);
			}
		}
	}
}

static void	check_vertically(t_data *data)
{
	int	i;
	int	j;

	j = -1;
	while (++j < data->width)
	{
		i = -1;
		while (++i < data->height)
		{
			while (i < data->height && data->map[i][j] == ' ')
				i++;
			if (!data->map[i])
				break ;
			if (data->map[i][j] != '1')
				ft_error("Error: map not enclosed horizontally\n", 1);
			else
			{
				while (i < data->height && data->map[i][j] != ' ')
					i++;
				if (data->map[i - 1][j] != '1')
					ft_error("Error: map not enclosed horizontally\n", 1);
			}
		}
	}
}

static int	valid_component(char c, int mode, int *cp)
{
	if (!mode)
	{
		if (c != '1' && c != '0' && c != 'N' && c != 'E' && c != 'W' \
		&& c != 'S' && c != ' ')
			return (0);
	}
	else
	{
		if (c != '1' && c != '0' && c != 'N' && c != 'E' && c != 'W' \
		&& c != 'S' && c != ' ' && c != 'D' && c != 'F' && c != 'T')
			return (0);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*cp)++;
	return (1);
}

static void	check_components(t_data *data, int mode)
{
	int	i;
	int	j;
	int	cp;

	i = -1;
	cp = 0;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
		{
			if (!valid_component(data->map[i][j], mode, &cp))
				ft_error("Error: invalid component in map\n", 1);
		}
	}
	if (cp != 1)
		ft_error("Error: missing or duplicate player position\n", 1);
}

void	check_walls(t_data *data, int mode)
{
	check_horizontal(data);
	check_vertically(data);
	check_components(data, mode);
}
