/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:49:49 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/04 15:42:01 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	int		x;
	int		y;
	float	dir;
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
	i = 0;
	while (map[i])
		printf("%s\n", map[i++]);
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

void	draw_screen(t_all *all)
{
	t_point	point;

	bzero(&point, sizeof(t_point));
	while (all->map[point.y])
	{
		point.x = 0;
		while (all->map[point.y][point.x])
		{
			if (all->map[point.y][point.x] == '1')
				mlx_pixel_put(all->win->mlx, all->win->win, point.x, point.y, 0xFFFFFF);
			point.x++;
		}
		point.y++;
	}
}

int main (int ac, char *av[])
{
	t_win	win;
	t_all	all;

	// if (ac == 2)
	// 	all.map = ft_read_map(av[1]);
	// else
	// 	return (printf("i need a map \n"), 2);
	win.mlx = mlx_init();
	// win.win = mlx_new_window(win.mlx, 640, 480, "RayCasting");
	// win.img = mlx_new_image(win.mlx, 640, 480);
	// win.addr = mlx_get_data_addr(win.img, &win.bpp, &win.line_l, &win.en);
	// all.win = &win;
	// draw_screen(&all);
	int	w, h;
	win.img = mlx_xpm_file_to_image(win.mlx, "test.xpm", &w, &h);
	printf("%d\n", win.img);
	mlx_loop(win.mlx);
	return (1);
}
