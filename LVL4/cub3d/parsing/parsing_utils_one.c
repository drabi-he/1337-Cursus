/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarchil <abarchil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 12:16:40 by atouhami          #+#    #+#             */
/*   Updated: 2022/03/06 19:31:58 by abarchil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	int		i;
	char	*psource;

	i = 0;
	psource = (char *)s;
	while (n)
	{
		psource[i] = (unsigned char)c;
		i++;
		n--;
	}
	return (s);
}

void	replace_nl_with_null(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			str[i] = '\0';
		i++;
	}
}

void	free_parsing(t_parsing *parsing)
{
	int	i;

	free(parsing->ea);
	free(parsing->no);
	free(parsing->we);
	free(parsing->so);
	free(parsing->tmpline);
	free(parsing->first_line);
	i = 0;
	while (parsing->map && parsing->map[i])
	{
		free(parsing->map[i]);
		parsing->map[i] = NULL;
		i++;
	}
	free(parsing->map);
	parsing->no = NULL;
	parsing->so = NULL;
	parsing->ea = NULL;
	parsing->we = NULL;
	parsing->tmpline = NULL;
	parsing->map = NULL;
	parsing->first_line = NULL;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	count;

	i = 0;
	sign = 1;
	count = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		count = count * 10 + str[i] - 48;
		i++;
	}
	return (count * sign);
}

char	*ft_strdup(char *source)
{
	int		i;
	char	*dst;

	i = 0;
	while (source[i])
		i++;
	dst = malloc(i * sizeof(char) + 1);
	if (dst == NULL)
		return (printf("Error : Failed allocation\n"), exit(1), NULL);
	i = 0;
	while (source[i])
	{
		dst[i] = source[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
