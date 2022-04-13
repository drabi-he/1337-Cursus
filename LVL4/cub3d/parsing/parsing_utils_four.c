/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_four.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:17:04 by atouhami          #+#    #+#             */
/*   Updated: 2022/04/06 14:45:11 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	parse_map(t_parsing *parsing, size_t i)
{
	parsing->count_lines += 1;
	parsing->biggest_lines = ft_strlen(parsing->first_line);
	while (1)
	{
		parsing->tmpline = get_next_line(parsing->fd);
		if (parsing->tmpline)
		{
			replace_nl_with_null(parsing->tmpline);
			if (ft_strlen(parsing->tmpline) > parsing->biggest_lines)
				parsing->biggest_lines = ft_strlen(parsing->tmpline);
			parsing->count_lines += 1;
			free(parsing->tmpline);
			parsing->tmpline = 0;
			continue ;
		}
		break ;
	}
	parsing->map = malloc(sizeof(char *) * (parsing->count_lines + 1));
	if (!parsing->map)
		return (free_parsing(parsing),
			printf("Error : Failed allocation\n"), exit(1));
	while (i < parsing->count_lines + 1)
		parsing->map[i++] = NULL;
}

int	check_fist_last_line(t_parsing *parsing)
{
	int	j;

	j = 0;
	while (parsing->map[0][j])
	{
		if (parsing->map[0][j] != '1' && parsing->map[0][j] != ' ')
			return (1);
		j++;
	}
	j = 0;
	while (parsing->map[parsing->count_lines - 1][j])
	{
		if (parsing->map[parsing->count_lines - 1][j] != '1'
			&& parsing->map[parsing->count_lines - 1][j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	check_first_indexes(t_parsing *parsing)
{
	int	j;

	j = 0;
	while (parsing->map[j] && parsing->map[j][0])
	{
		if (parsing->map[j][0] != '1' && parsing->map[j][0] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	check_map(t_parsing *parsing, int i, int j)
{
	if (check_fist_last_line(parsing) || check_first_indexes(parsing))
		return (free_parsing(parsing), printf("Error: \
		Map not enclosed by walls\n"), 1);
	while (parsing->map[i])
	{
		j = 0;
		while (parsing->map[i][j])
		{
			if (parsing->map[i][j] == ' ' && (
			(i > 0 && parsing->map[i - 1][j] != '1'
			&& parsing->map[i - 1][j] != ' ') || (j > 0
			&& parsing->map[i][j - 1] != '1'
			&& parsing->map[i][j - 1] != ' ')
			|| (i < (int)parsing->count_lines - 1
			&& parsing->map[i + 1][j] != '1'
			&& parsing->map[i + 1][j] != ' ')
			|| (j < (int)parsing->biggest_lines - 1
			&& parsing->map[i][j + 1] != '1'
			&& parsing->map[i][j + 1] != ' ')))
				return (free_parsing(parsing),
					printf("Error: Map not enclosed by walls\n"), 1);
			j++;
		}
		i++;
	}
	return (0);
}

void	parse_map_assign_two(t_parsing *parsing, size_t *i)
{
	parsing->map[*i] = malloc(sizeof(char) * parsing->biggest_lines + 1);
	if (!parsing->map[*i])
		return (free_parsing(parsing),
			printf("Error : Failed allocation\n"), exit(1));
	if (parsing->tmpline[0] == '\n')
		return (free_parsing(parsing),
			printf("Error: newline found\n"), exit(1));
	ft_memset(parsing->map[*i], ' ', parsing->biggest_lines);
	parsing->map[*i][parsing->biggest_lines] = '\0';
	replace_nl_with_null(parsing->tmpline);
	ft_memmove(parsing->map[*i], parsing->tmpline,
		ft_strlen(parsing->tmpline));
	*i += 1;
	free(parsing->tmpline);
	parsing->tmpline = NULL;
}
