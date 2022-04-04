/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:58:27 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/04 13:07:30 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strchr(char *s, int c)
{
	int	i;

	if ((char)c == '\0')
		return ((char *)(s + ft_strlen(s)));
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	return (NULL);
}

void	pixel_put(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (x * (win->bits_per_pixel / 8) + y * win->size_line);
	*(int *)dst = color;
}

void	pixel_put_mini(t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr_mini + (x * (win->bpp / 8) + y * win->sl);
	*(int *)dst = color;
}

void	ft_verline(t_win *win, unsigned int **buffer, int mode)
{
	int	i;
	int	j;

	i = -1;
	while (++i < SCREEN_H)
	{
		j = -1;
		while (++j < SCREEN_W)
		{
			if (mode)
				pixel_put(win, j, i, buffer[i][j]);
			else
				buffer[i][j] = 0;
		}
	}
}

float	f_abs(float n)
{
	if (n >= 0)
		return (n);
	return (-n);
}
