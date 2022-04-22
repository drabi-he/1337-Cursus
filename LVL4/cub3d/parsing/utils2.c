/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:14:28 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/22 14:59:27 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static char	*get_texture_name(char *line)
{
	int		i;
	int		fd;
	char	*trim;

	i = 0;
	trim = ft_strtrim(line, " \t\f\v\r\n");
	fd = open(trim, O_RDONLY, 0644);
	if (fd == -1)
		ft_error("Error: non-existent texture\n", 1);
	close (fd);
	return (trim);
}

void	ft_check_texture(t_data *data, char c, char *line, int *cp)
{
	if (data->bola[(int) c] == 1)
		ft_error("Error: duplicate texture value\n", 1);
	data->bola[(int) c] = 1;
	(*cp)++;
	if (c == 'N')
		data->no = get_texture_name(line + 3);
	if (c == 'S')
		data->so = get_texture_name(line + 3);
	if (c == 'E')
		data->ea = get_texture_name(line + 3);
	if (c == 'W')
		data->we = get_texture_name(line + 3);
}

void	stupid_copy(t_data *data)
{
	int		i;
	int		j;
	char	*copy;

	copy = malloc ((data->width + 1) * sizeof(char));
	(!copy && ft_error("Error: allocation failed\n", 1));
	i = -1;
	while (data->map[++i])
	{
		j = -1;
		while (data->map[i][++j])
			copy[j] = data->map[i][j];
		while (j < data->width)
			copy[j++] = ' ';
		copy[j] = 0;
		free(data->map[i]);
		data->map[i] = ft_strdup(copy);
	}
	free (copy);
}

static void	mini_loop(int fd, t_data *data)
{
	char	*trim;

	while (1)
	{
		data->map[0] = get_next_line(fd);
		trim = ft_strtrim(data->map[0], " \t\n\r\v\f");
		if (trim && trim[0] == '1')
		{
			free (trim);
			return ;
		}
		free(data->map[0]);
		free(trim);
	}
}

void	fill_map(t_data *data, char *filename)
{
	int		fd;
	int		i;

	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		ft_error("Error: file doesn't exist o r permission denied\n", 1);
	data->map = malloc((data->height + 1) * sizeof(char *));
	(!data->map && ft_error("Error: allocation failed\n", 1));
	mini_loop(fd, data);
	data->width = 0;
	i = 0;
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) > (size_t) data->width)
			data->width = (int) ft_strlen(data->map[i]);
		data->map[++i] = get_next_line(fd);
	}
	(i != data->height && ft_error("Error: newline in map\n", 1));
	stupid_copy(data);
}
