/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_seven.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 21:43:43 by atouhami          #+#    #+#             */
/*   Updated: 2022/04/06 14:47:27 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	search_for_player2(t_parsing *parsing, int i, int j, int count)
{
	while (parsing->map[i])
	{
		j = 0;
		while (parsing->map[i][j])
		{
			if (parsing->map[i][j] != '1' && parsing->map[i][j] != ' '
				&& parsing->map[i][j] != '0' && parsing->map[i][j] != 'N'\
				&& parsing->map[i][j] != 'S' && parsing->map[i][j] != 'E'\
				&& parsing->map[i][j] != 'W' && parsing->map[i][j] != 'D'\
				&& parsing->map[i][j] != 'F')
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

int	ft_isdigit(int character)
{
	if (character >= '0' && character <= '9')
		return (1);
	return (0);
}

int	check_colors(char *str)
{
	int	i;
	int	count;

	i = 1;
	count = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != ',') || count > 2)
			return (1);
		if (str[i] == ',')
			count++;
		i++;
	}
	return (0);
}
