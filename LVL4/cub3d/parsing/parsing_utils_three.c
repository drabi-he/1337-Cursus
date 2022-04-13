/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_three.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:16:59 by atouhami          #+#    #+#             */
/*   Updated: 2022/04/06 14:53:43 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	assign_vars(t_parsing *parsing)
{
	int	i;

	replace_nl_with_null(parsing->tmpline);
	if (assign_vars_two(parsing, 0))
		return (1);
	if (parsing->tmpline[0] == 'E' && parsing->tmpline[1]
		== 'A' && parsing->tmpline[2] == ' ')
	{
		if (parsing->ea != NULL)
			return (free_parsing(parsing),
				printf("Error : Duplicate EA\n"), 1);
		i = skip_spaces(parsing->tmpline);
		parsing->ea = ft_strdup(parsing->tmpline + i);
		parsing->counter += 1;
	}
	if (parsing->tmpline && parsing->tmpline[0] == 'F'
		&& parsing->tmpline[1] == ' ')
		if (assign_floor(parsing, 2))
			return (1);
	if (parsing->tmpline && parsing->tmpline[0] == 'C'
		&& parsing->tmpline[1] == ' ')
		if (assign_ceiling(parsing, 2))
			return (1);
	return (0);
}

void	init_parsing(t_parsing *parsing, char *argv[])
{
	parsing->index = 0;
	parsing->counter = 0;
	parsing->skip_lines = 0;
	parsing->biggest_lines = 0;
	parsing->count_lines = 0;
	parsing->argv = argv;
	parsing->no = NULL;
	parsing->so = NULL;
	parsing->ea = NULL;
	parsing->we = NULL;
	parsing->fd = open(argv[1], O_RDONLY);
	parsing->map = NULL;
	parsing->first_line = NULL;
	parsing->color_ceiling = -1;
	parsing->color_floor = -1;
}

void	parsing_directions_colors_two(t_parsing *parsing)
{
	parsing->tmpline = get_next_line(parsing->fd);
	if (!(parsing->tmpline))
		return (free_parsing(parsing),
			printf("Error: missing informations\n"), exit(1));
	parsing->skip_lines += 1;
}

int	parsing_directions_colors(t_parsing *parsing, char *argv[], int argc)
{
	if (argc != 2 || check_file_name(argv[1]) == -1)
		return (printf("Error : Invalid arguments\n"), 1);
	init_parsing(parsing, argv);
	if (parsing->fd == -1)
		return (printf("Error : file doesn't exist or permission denied\n"), 1);
	while (parsing->index != 6)
	{
		parsing_directions_colors_two(parsing);
		if (parsing->tmpline[0] == '\n')
		{
			free(parsing->tmpline);
			parsing->tmpline = NULL;
			continue ;
		}
		if (assign_vars(parsing))
			return (1);
		free(parsing->tmpline);
		parsing->tmpline = NULL;
		parsing->index += 1;
	}
	if (parsing->index != parsing->counter || !parsing->so
		|| !parsing->we || !parsing->no || !parsing->ea)
		return (free_parsing(parsing), printf("Error : \
		missing informations\n"), 1);
	return (0);
}

int	skip_newlines(t_parsing *parsing)
{
	while (1)
	{
		parsing->tmpline = get_next_line(parsing->fd);
		if (!parsing->tmpline)
			return (free_parsing(parsing), printf("Error: \
			missing informations\n"), 1);
		parsing->skip_lines += 1;
		if (parsing->tmpline[0] == '\n')
		{
			free(parsing->tmpline);
			parsing->tmpline = NULL;
			continue ;
		}
		else
			break ;
	}
	parsing->first_line = ft_strdup(parsing->tmpline);
	free(parsing->tmpline);
	parsing->tmpline = NULL;
	return (0);
}
