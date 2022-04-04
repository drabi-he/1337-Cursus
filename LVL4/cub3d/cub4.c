/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:49:49 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/01 18:30:09 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	WIDTH 1240
#define	HEIGHT 1080
#define SCALE 10

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_win
{
	void	*mlx;
	void	*win;
	void	*img;
	void	*addr;
	int		line_l;
	int		bpp;
	int		en;
}	t_win;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_plr
{
	float	x;
	float	y;
	float	dir;
	float	start;
	float	end;
}	t_plr;

typedef struct s_all
{
	t_win	*win;
	t_plr	*plr;
	char	**map;
}	t_all;

size_t	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int		ft_close(void)
{
	exit(0);
}

char	*ft_strdup(char *s1)
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
	if (buff[0] == 0)
		return (NULL);
	return (ft_strdup(buff));
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cp;

	if (!lst[0])
	{
		lst[0] = new;
		return ;
	}
	cp = lst[0];
	while (cp->next)
		cp = cp->next;
	cp->next = new;
}

int		ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*cp;

	cp = lst;
	i = 0;
	while (cp)
	{
		cp = cp->next;
		i++;
	}
	return (i);
}

char 	**ft_make_map(t_list **head, int amount)
{
	t_list	*tmp = *head;
	char	**map = calloc(amount + 1, sizeof(char *));
	int		i = 0;

	while (tmp)
	{
		map[i] = tmp->content;
		i++;
		tmp = tmp->next;
	}
	// i = 0;
	// while (map[i])
	// 	printf("%s\n", map[i++]);
	return (map);
}

char	**ft_read_map(char *av1)
{
	char	*str = 0;
	t_list	*head = 0;
	int		amount = 0;
	int		fd = open(av1, O_RDONLY);

	str = get_next_line(fd);
	while (str)
	{
		ft_lstadd_back(&head, ft_lstnew(str));
		amount++;
		str = get_next_line(fd);
	}
	close(fd);
	ft_lstadd_back(&head, ft_lstnew(str));
	amount++;
	return (ft_make_map(&head, amount));
}

void	pixel_put (t_win *win, int x, int y, int color)
{
	char	*dst;

	dst = win->addr + (x * (win->bpp / 8) + y * win->line_l);
	*(int *)dst = color;
}

void	ft_init_player(char	**map, t_plr *plr)
{
	t_point	pos;

	bzero(&pos, sizeof(t_point));
	while (map[pos.y])
	{
		pos.x = 0;
		while (map[pos.y][pos.x])
		{
			if (strchr("NEWS", map[pos.y][pos.x]))
			{
				plr->x = pos.x * SCALE;
				plr->y = pos.y * SCALE;
				plr->dir = 3 * M_PI_2;
			}
			pos.x++;
		}
		pos.y++;
	}
}

void	ft_draw_player(t_all *all, t_plr *pl)
{
	t_plr	plr = *all->plr;

	// plr.start = plr.dir - M_PI_4;
	// plr.end = plr.dir + M_PI_4;
	// while (plr.start < plr.end)
	// {
	// 	plr.x = pl->x;
	// 	plr.y = pl->y;
		while (all->map[(int)(plr.y / SCALE)][(int)(plr.x / SCALE)] != '1')
		{
			printf("dist = %d | %d \n", plr.x , plr.y);
			plr.x += cos(plr.dir);
			plr.y += sin(plr.dir);
			pixel_put(all->win, plr.x, plr.y, 0x00FFFF);
		// }
		// plr.start += M_PI_2 / 640;
	}
}

void	ft_draw_player2(t_all *all, t_plr *pl)
{
	t_point	start;
	t_point	end;

	start.x = all->plr->x - 5;
	start.y = all->plr->y - 5;
	end.x = start.x + 10;
	end.y = start.y + 10;
	while (start.y < end.y)
	{
		while (start.x < end.x)
			pixel_put(all->win, start.x++, start.y, 0xFF0000);
		start.x -= 10;
		start.y++;
	}
}

void	ft_scale_img(t_win *win, t_point point, int color)
{
	t_point	end;

	end.x = (point.x + 1) * SCALE;
	end.y = (point.y + 1) * SCALE;
	point.x *= SCALE;
	point.y *= SCALE;
	while (point.y <  end.y)
	{
		while (point.x < end.x)
			pixel_put(win, point.x++, point.y, color);
		point.x -= SCALE;
		point.y++;
	}
}

void	draw_screen(t_all *all)
{
	t_point	point;
	t_win *win = all->win;

	win->img = mlx_new_image(win->mlx, WIDTH, HEIGHT);
	win->addr = mlx_get_data_addr(win->img, &win->bpp, &win->line_l, &win->en);
	bzero(&point, sizeof(t_point));
	while (all->map[point.y])
	{
		point.x = 0;
		while (all->map[point.y][point.x])
		{
			if (all->map[point.y][point.x] == '1')
				ft_scale_img(all->win, point, 0xFFFFFF);
			point.x++;
		}
		point.y++;
	}
	ft_draw_player(all, all->plr);
	ft_draw_player2(all, all->plr);
	mlx_put_image_to_window(win->mlx, win->win, win->img, 0, 0);
	mlx_destroy_image(win->mlx, win->img);
}

int		key_press(int key, t_all *all)
{
	mlx_clear_window(all->win->mlx, all->win->win);
	if (key == 13)
	{
		all->plr->y += sin(all->plr->dir) * 4;
		all->plr->x += cos(all->plr->dir) * 4;
		if (all->map[(int)(all->plr->y / SCALE)][(int)(all->plr->x / SCALE)] == '1')
		{
			all->plr->y -= sin(all->plr->dir) * 4;
			all->plr->x -= cos(all->plr->dir) * 4;
		}
	}
	if (key == 1)
	{
		all->plr->y -= sin(all->plr->dir) * 4;
		all->plr->x -= cos(all->plr->dir) * 4;
		if (all->map[(int)(all->plr->y / SCALE)][(int)(all->plr->x / SCALE)] == '1')
		{
			all->plr->y += sin(all->plr->dir) * 4;
			all->plr->x += cos(all->plr->dir) * 4;
		}
	}
	// if (key == 0)
	// {
	// 	all->plr->y += sin(all->plr->dir) * 4;
	// 	all->plr->x -= cos(all->plr->dir) * 4;
	// }
	// if (key == 2)
	// {
	// 	all->plr->y -= sin(all->plr->dir) * 4;
	// 	all->plr->x += cos(all->plr->dir) * 4;
	// }
	if (key == 123)
		all->plr->dir -= 0.1;
	if (key == 124)
		all->plr->dir += 0.1;
	if (key == 53)
		ft_close();
	draw_screen(all);
	return (0);
}

int main (int ac, char *av[])
{
	t_win	win;
	t_plr	plr;
	t_all	all;

	if (ac == 2)
		all.map = ft_read_map(av[1]);
	else
		return (printf("i need a map \n"), 2);
	ft_init_player(all.map, &plr);
	win.mlx = mlx_init();
	win.win = mlx_new_window(win.mlx, WIDTH, HEIGHT, "RayCasting");
	win.img = mlx_new_image(win.mlx, WIDTH, HEIGHT);
	win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);
	all.plr = &plr;
	all.win = &win;
	draw_screen(&all);
	mlx_hook(win.win, 2, (1L << 0), key_press, &all);
	mlx_hook(win.win, 17, 0, ft_close, NULL);
	mlx_loop(win.mlx);
	return (1);
}
