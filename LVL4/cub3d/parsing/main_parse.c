/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:12:23 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/07 17:16:08 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	search_for_player(t_parsing *parsing, int i, int j, int count)
{
	while (parsing->map[i])
	{
		j = 0;
		while (parsing->map[i][j])
		{
			if (parsing->map[i][j] != '1' && parsing->map[i][j] != ' '
				&& parsing->map[i][j]
				!= '0' && parsing->map[i][j] != 'N' && parsing->map[i][j]
				!= 'S' && parsing->map[i][j] != 'E' && parsing->map[i][j]
				!= 'W')
				return (free_parsing(parsing),
					printf("Error: invalid identifier\n"), 1);
			else if (parsing->map[i][j] == 'N' || parsing->map[i][j] == 'S'
			|| parsing->map[i][j] == 'E' || parsing->map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		return (free_parsing(parsing), printf("Error: duplicate or \
			non-existent player\n"), 1);
	return (0);
}

void	ft_debug(t_parsing *parsing)
{
	int	i;

	i = 0;
	printf("%s\n%s\n%s\n%s\n", parsing->no, parsing->we, parsing->ea, parsing->so);
	printf("F %d %d %d | C %d %d %d\n", parsing->floor_red,
		parsing->floor_green, parsing->floor_blue, parsing->ceiling_red,
		parsing->ceiling_green, parsing->ceiling_blue);
	while (parsing->map[i])
		printf("- %s-\n", parsing->map[i++]);
}

int	ft_check_file(t_parsing *parsing)
{
	int	ea;
	int	we;
	int	so;
	int	no;

	ea = open(parsing->ea, O_RDONLY);
	we = open(parsing->we, O_RDONLY);
	so = open(parsing->so, O_RDONLY);
	no = open(parsing->no, O_RDONLY);
	if (no == -1 || ea == -1 || we == -1 || so == -1)
		return (free_parsing(parsing),
			printf("Error : invalid texture files"), 1);
	close(ea);
	close(we);
	close(so);
	close(no);
	return (0);
}

int	assign_vars_three(t_parsing *parsing, int i)
{
	if (parsing->tmpline[0] == 'W' && parsing->tmpline[1]
		== 'E' && parsing->tmpline[2] == ' ')
	{
		if (parsing->we != NULL)
			return (free_parsing(parsing), printf("Error : Duplicate WE\n"), 1);
		i = skip_spaces(parsing->tmpline);
		parsing->we = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}
	return (0);
}

void	main_parse(int ac, char **av, t_parsing *parsing, int mode)
{
	if (parsing_directions_colors(parsing, av, ac)
		|| skip_newlines(parsing))
		exit(1);
	parse_map(parsing, 0);
	parse_map_assign(parsing, 0);
	if (check_map(parsing, 0, 0))
		exit(1);
	if (mode == MANDATORY && (search_for_player(parsing, 0, 0, 0) \
	|| ft_check_file(parsing)))
		exit(1);
	if (mode == BONUS && (search_for_player2(parsing, 0, 0, 0) \
	|| ft_check_file(parsing)))
		exit(1);
	close(parsing->fd);
}
