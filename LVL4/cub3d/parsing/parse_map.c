/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:44:23 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/22 14:24:34 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_line(char *line, t_data *data, int *cp)
{
	if (line[0] == 'C' && ft_isspace(line[1]))
		ft_check_color(data, line[0], line, cp);
	else if (line[0] == 'F' && ft_isspace(line[1]))
		ft_check_color(data, line[0], line, cp);
	else if (line[0] == 'N' && line[1] == 'O' && ft_isspace(line[2]))
		ft_check_texture(data, line[0], line, cp);
	else if (line[0] == 'S' && line[1] == 'O' && ft_isspace(line[2]))
		ft_check_texture(data, line[0], line, cp);
	else if (line[0] == 'E' && line[1] == 'A' && ft_isspace(line[2]))
		ft_check_texture(data, line[0], line, cp);
	else if (line[0] == 'W' && line[1] == 'E' && ft_isspace(line[2]))
		ft_check_texture(data, line[0], line, cp);
	else
		ft_error("Error: invalid informations\n", 1);
	free(line);
}

void	check_map_infos(int fd, t_data *data)
{
	char		*line;
	char		*tmp;
	static int	cp;

	tmp = get_next_line(fd);
	line = ft_strtrim(tmp, " \t\r\f\v\n");
	if (line && line[0] == '1' && cp != 6)
		ft_error("Error: missing informations\n", 1);
	if (line && line[0] == '1')
	{
		count_height(fd, data);
		free(line);
		free(tmp);
		return ;
	}
	if (line)
		parse_line(line, data, &cp);
	free(tmp);
	check_map_infos(fd, data);
}

void	parse_map(int ac, char *filename, t_data *data, int mode)
{
	int	fd;

	if (ac != 2)
		ft_error("Error: Wrong Arguments Count\n", 1);
	if (ft_strcmp(".cub", filename + ft_strlen(filename) - 4))
		ft_error("Error: Wrong file format\n", 1);
	fd = open(filename, O_RDONLY, 0644);
	if (fd == -1)
		ft_error("Error: file doesn't exist or permission denied\n", 1);
	check_map_infos(fd, data);
	close (fd);
	fill_map(data, filename);
	check_walls(data, mode);
}
