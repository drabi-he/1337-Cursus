/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:31:14 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/22 14:46:02 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	is_valid(char *line)
{
	int	i;
	int	cp;

	i = 0;
	cp = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	while (line[i])
	{
		if ((line[i] >= '0' && line[i] <= '9') || line[i] == ',')
		{
			if (line[i] == ',')
				cp++;
		}
		else
			ft_error("Error: invalid RGB format\n", 1);
		i++;
	}
	if (cp != 2)
		ft_error("Error: invalid RGB format\n", 1);
}

static int	rgb_to_int(char *line)
{
	int	i;
	int	j;

	is_valid(line);
	i = 0;
	while (line[i] != ',')
		i++;
	if (line[++i] == ',')
		ft_error("Error: duplicate color value\n", 1);
	j = i;
	while (line[j] != ',')
		j++;
	if (j == i || line[++j] == ',')
		ft_error("Error: invalid RGB format\n", 1);
	if (!line[0] || !line[i] || !line[j])
		ft_error("Error: invalid RGB format\n", 1);
	return (ft_atoi(line) * 65536 + ft_atoi(line + i) * 256 \
	+ ft_atoi(line + j));
}

void	ft_check_color(t_data *data, char c, char *line, int *cp)
{
	if (data->bola[(int) c] == 1)
		ft_error("Error: duplicate color value\n", 1);
	data->bola[(int) c] = 1;
	(*cp)++;
	if (c == 'C')
		data->ceiling = rgb_to_int(line + 2);
	if (c == 'F')
		data->floor = rgb_to_int(line + 2);
}

void	count_height(int fd, t_data *data)
{
	int		cp;
	char	c;

	cp = 1;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			cp++;
	}
	data->height = ++cp;
}

void	free_all(t_data *data, t_all *all)
{
	int	i;

	free(data->no);
	free(data->so);
	free(data->ea);
	free(data->we);
	i = -1;
	while (data->map[++i])
		free(data->map[i]);
	free(data->map);
	i = -1;
	while (++i < SCREEN_H)
		free(all->ray->buffer[i]);
	free(all->ray->buffer);
}
