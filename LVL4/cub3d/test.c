/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 10:48:04 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/30 11:18:32 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define mapWidth 7
#define mapHeight 7
#define screenWidth 640
#define screenHeight 480
#define drawline 10

typedef struct s_display
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_display;

typedef struct s_player
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	a;
}	t_player;

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_all
{
	t_display	dis;
	char		**map;
	t_player	player;
}	t_all;

size_t	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	ft_close(void)
{
	exit(0);
}

static char	*ft_strdup(char *s1)
{
	char	*copy;
	int		i;

	copy = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
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
	return (ft_strdup(buff));
}

int	map_height()
{
	int		fd;
	char	*line;
	int		cp;
	char	c;

	cp = 0;
	fd = open("map1.cub", O_RDONLY, 0644);
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			cp++;
	}
	close (fd);
	return (++cp);
}

char	**read_map()
{
	char	**map;
	int		fd;
	int 	i;

	i = 0;
	map_height();
	map = malloc((map_height() + 1) * sizeof(char *));
	fd = open("map1.cub", O_RDONLY, 0644);
	while (1)
	{
		map[i] = get_next_line(fd);
		if (map[i][0] == '\0')
			break ;
		i++;
	}
	map[i] = 0;
	return (map);
}

t_player	get_player(char **map)
{
	t_player player;
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (strchr("NEWS", map[i][j]))
			{
				player.x = j;
				player.y = i;
			}
			j++;
		}
		i++;
	}
	return (player);
}

void	pixel_put(t_display *dis, int x, int y, int color)
{
	char *dst;

	dst = dis->addr + (y * dis->size_line + x * (dis->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_player(t_display *dis, t_player player)
{
	t_point	end;
	t_point	start;

	end.y = player.y * drawline + drawline;
	start.y = player.y * drawline;
	end.x = player.x * drawline + drawline;
	start.x = player.x * drawline;
	while (start.y < end.y)
	{
		while (start.x < end.x)
			pixel_put(dis, start.x++, start.y, 0x00FFFF);
		start.x -= drawline;
		start.y++;
	}
}

void	draw_map(t_display *dis, char **map, t_player pl)
{
	t_point	end;
	t_point	start;
	int		i;
	int		j;

	dis->img = mlx_new_image(dis->mlx, screenWidth, screenHeight);
	dis->addr = mlx_get_data_addr(dis->img, &dis->bits_per_pixel,\
	 			&dis->size_line, &dis->endian);
	i = 0;
	while (map[i])
	{
		j = 0;
		end.y = i * drawline + drawline - 1;
		start.y = i * drawline;
		while (map[i][j])
		{
			end.x = j * drawline + drawline - 1;
			start.x = j * drawline;
			if (map[i][j] == '1')
			while (start.y < end.y)
			{
				while (start.x < end.x)
					pixel_put(dis, start.x++, start.y, 0xFFFFFF);
				start.x -= drawline - 1;
				start.y++;
			}
			//if (map[i][j] == '1')
			start.y -= drawline - 1;
			j++;
		}
		i++;
	}
	draw_player(dis, pl);
	mlx_put_image_to_window(dis->mlx, dis->win, dis->img, 0, 0);
	mlx_destroy_image(dis->mlx, dis->img);
}

int	ft_movements(int keypress, t_all *all)
{
	mlx_clear_window(all->dis.mlx, all->dis.win);
	if (keypress == 13 || keypress == 124)
	{
		all->player.x += all->player.dx;
		all->player.y += all->player.dy;
	}
	if (keypress == 1 || keypress == 123)
	{
		all->player.x -= all->player.dx;
		all->player.y -= all->player.dy;
	}
	if (keypress == 2 || keypress == 126)
	{
		all->player.a -= 0.1;
		if (all->player.a < 0)
			all->player.a += 2 * M_PI;
		all->player.dx = cos(all->player.a) * 5;
		all->player.dy = sin(all->player.a) * 5;
	}
	if (keypress == 0 || keypress == 125)
	{
		all->player.a += 0.1;
		if (all->player.a > 2 * M_PI)
			all->player.a -= 2 * M_PI;
		all->player.dx = cos(all->player.a) * 5;
		all->player.dy = sin(all->player.a) * 5;
	}
	if (keypress == 53)
		ft_close();
	draw_map(&all->dis, all->map, all->player);
	return (0);
}

t_all all_init()
{
	t_all	all;

	all.map = read_map();
	all.player = get_player(all.map);
	all.dis.mlx = mlx_init();
	all.dis.win = mlx_new_window(all.dis.mlx, screenWidth, screenHeight, "RayCasting");
	all.dis.img = mlx_new_image(all.dis.mlx, screenWidth, screenHeight);
	all.dis.addr = mlx_get_data_addr(all.dis.img, &all.dis.bits_per_pixel,\
	 				&all.dis.size_line, &all.dis.endian);
	return (all);
}

int main()
{
	t_all	all;


	all = all_init();
	draw_map(&all.dis, all.map, all.player);
	mlx_hook(all.dis.win, 2, 0, ft_movements, &all);
	mlx_hook(all.dis.win, 17, 0, ft_close, NULL);
	mlx_loop(all.dis.mlx);
	return (0);
}
