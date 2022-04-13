/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_six.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:17:13 by atouhami          #+#    #+#             */
/*   Updated: 2022/04/05 22:09:47 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*first_line(char *str)
{
	int		i;
	char	*line;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n' && str)
		i++;
	line = malloc(i + 2);
	if (!line)
		return (printf("Error : Failed allocation\n"), exit(1), NULL);
	ft_memmove(line, str, i + 1);
	line[i + 1] = '\0';
	return (line);
}

char	*second_part(char *str)
{
	int		i;
	char	*line;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	line = malloc(ft_strlen(&str[i]) + 1);
	if (!line)
		return (printf("Error : Failed allocation\n"), exit(1), NULL);
	ft_memmove(line, &str[i + 1], ft_strlen(&str[i]));
	line[ft_strlen(&str[i])] = '\0';
	free (str);
	if (ft_strlen(line) == 0)
		return (free(line), NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		buff[2];
	int			readc;

	line = NULL;
	if (fd < 0 || 1 <= 0)
		return (NULL);
	readc = 1;
	while (readc != 0 && !(contains_newline(str)))
	{
		readc = read(fd, buff, 1);
		if (readc == -1)
			return (NULL);
		buff[readc] = '\0';
		if (!readc)
			break ;
		str = ft_strjoin(str, buff);
	}
	line = first_line(str);
	str = second_part(str);
	return (line);
}

void	parse_map_assign(t_parsing *parsing, size_t i)
{
	close(parsing->fd);
	parsing->fd = open(parsing->argv[1], O_RDONLY);
	while (i < parsing->skip_lines - 1)
	{
		parsing->tmpline = get_next_line(parsing->fd);
		free(parsing->tmpline);
		parsing->tmpline = NULL;
		i++;
	}
	i = 0;
	while (i < parsing->count_lines)
	{
		parsing->tmpline = get_next_line(parsing->fd);
		if (parsing->tmpline)
		{
			parse_map_assign_two(parsing, &i);
			continue ;
		}
		break ;
	}
}

void	replace_spc_wall(t_parsing *parsing)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parsing->map[i])
	{
		j = 0;
		while (parsing->map[i][j])
		{
			if (parsing->map[i][j] == ' ')
				parsing->map[i][j] = '1';
			j++;
		}
		i++;
	}
}
