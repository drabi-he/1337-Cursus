/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:54:23 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/22 14:58:59 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*copy;
	int		i;

	if (!str)
		return (NULL);
	copy = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!copy)
		ft_error("Error: allocation failed\n", 1);
	i = -1;
	while (str[++i])
		copy[i] = str[i];
	copy[i] = 0;
	return (copy);
}

char	*get_next_line(int fd)
{
	char	buff[8000000];
	char	c;
	int		i;

	i = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			break ;
		buff[i] = c;
		i++;
	}
	buff[i] = 0;
	if (buff[0] == 0)
		return (NULL);
	return (ft_strdup(buff));
}

int	ft_get_index(char const *str, char const *set, int cp, int index)
{
	size_t	j;

	j = 0;
	while (set[j])
	{
		if (str[index] == set[j])
		{
			j = 0;
			index += cp;
		}
		else
			j++;
	}
	return (index);
}

char	*ft_strtrim(char *s1, char const *set)
{
	char	*rst;
	int		i;
	int		len;
	int		j;

	if (!s1)
		return (NULL);
	i = ft_get_index(s1, set, 1, 0);
	len = ft_get_index(s1, set, -1, ft_strlen(s1) - 1);
	rst = (char *)malloc((len - i + 2) * sizeof(char));
	if (!rst)
		ft_error("Error: allocation failed\n", 1);
	j = 0;
	while (i <= len)
		rst[j++] = s1[i++];
	rst[j] = 0;
	return (rst);
}
