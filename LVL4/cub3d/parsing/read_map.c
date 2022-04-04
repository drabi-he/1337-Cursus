/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:48:41 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/31 18:50:34 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_map_format(char *str)
{
	char	*tmp;
	int		fd;

	fd = open(str, O_RDONLY, 0644);
	if (fd == -1)
		ft_error("Error: file doesn't exist or permission denied\n", 1);
	close(fd);
	tmp = ft_strstr(str, ".cub");
	if (ft_strcmp(tmp, ".cub\0"))
		ft_error("Error: wrong map format <filename>.cub\n", 1);
}

static char	**ft_make_map(char *str, int amount)
{
	char	**map;
	int		fd;
	int		i;

	map = (char **) malloc((amount + 1) * sizeof(char *));
	if (!map)
		return (ft_error("Error: allocation failed\n", 1), NULL);
	fd = open(str, O_RDONLY, 0644);
	i = 0;
	map[0] = get_next_line(fd);
	while (map[i])
		map[++i] = get_next_line(fd);
	map[i] = 0;
	if (i < amount)
		ft_error("Error: there is an empty newline in th map\n", 1);
	return (map);
}

static char	**map_init(char *str)
{
	char	c;
	int		amount;
	int		fd;

	fd = open(str, O_RDONLY, 0644);
	amount = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			amount++;
	}
	close(fd);
	amount++;
	return (ft_make_map(str, amount));
}

static void	get_dimension(char	**map, int *h, int *w)
{
	int	i;

	i = 0;
	*w = 0;
	while (map[i])
	{
		if (*w < ft_strlen(map[i]))
			*w = ft_strlen(map[i]);
		i++;
	}
	*h = i;
}

void	read_map(t_all *all, char *str)
{
	check_map_format(str);
	all->map = map_init(str);
	get_dimension(all->map, &all->max_height, &all->max_width);
	//check_walls(all);
}
