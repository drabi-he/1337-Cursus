/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:36:14 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/28 16:03:04 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"

typedef struct s_map
{
	char	**map;
	int		length;
	int		width;
	int		collect;
	int		exit;
}	t_map;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_map	*map;
	void	*wall;
	void	*collect;
	void	*empty;
	void	*exit;
	void	*player;
}	t_vars;

//utils
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strstr(char *str, char *to_find)
{
	size_t	i;
	size_t	j;

	if (to_find[0] == '\0')
		return (str);
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0')
			{
				return (str + i);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *s1)
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
	char	i;

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

void	ft_affiche(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

// map check
void	ft_check_args(int ac, char **av)
{
	char	*tmp;

	if (ac == 1)
	{
		printf("please entre map path !!\n");
		exit(0);
	}
	else if (ac > 2)
	{
		printf("too many arguments !!\n");
		exit(0);
	}
	else
	{
		if (ft_strcmp(".ber", ft_strstr(av[1], ".ber\0")))
		{
			printf("map format error !!\n");
			exit(0);
		}
	}
}

int	ft_get_lines(char *map)
{
	int		fd;
	int		lines;
	char	c;

	fd = open(map, O_RDONLY);
	if (fd < 3)
	{
		printf("file not found or permission denied !!\n");
		exit(0);
	}
	lines = 0;
	while (read(fd, &c, 1))
	{
		if (c == '\n')
			lines++;
	}
	close(fd);
	return (++lines);
}

void	ft_check_width(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		if (ft_strlen(map->map[i]) != map->width)
		{
			printf("all line should have the same width !!\n");
			exit(0);
		}
		i++;
	}
}

void	ft_check_valid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
				&& map->map[i][j] != 'C' && map->map[i][j] != 'P'
				&& map->map[i][j] != 'E')
			{
				printf("invalid component found !!\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void	ft_check_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if ((map->map[i][j] != '1' && (i == 0 || i == map->length - 1))
				|| ((map->map[i][0] != '1' || map->map[i][map->width -1] != '1')
				&& (i != 0 || i != map->length - 1)))
			{
				printf("Walls error !!\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void	ft_process_map(t_map *map, char *path)
{
	int	fd;
	int	length;
	int	width;
	int	i;

	length = ft_get_lines(path);
	map->map = (char **)malloc((length + 1) * sizeof(char *));
	fd = open(path, O_RDONLY);
	if (fd < 3)
	{
		printf("file not found or permission denied !!\n");
		exit(0);
	}
	i = 0;
	while (i < length)
	{
		map->map[i] = get_next_line(fd);
		i++;
	}
	map->length = length;
	map->width = ft_strlen(map->map[0]);
	map->map[i] = 0;
}

void	ft_mini_init(int *a, int *b, int *c, int *d)
{
	*a = 1;
	*b = 0;
	*c = 0;
	*d = 0;
}

void	ft_mini_check(int a, int b, int c)
{
	if (a == 0 || b == 0 || c != 1)
	{
		printf("components error");
		printf("(1 player | >= 1 collectible | >= 1 Exit) !!\n");
		exit(0);
	}
}

void	ft_check_components(t_map *map)
{
	int	i;
	int	j;
	int	is_exit;
	int	is_collect;
	int	is_player;

	ft_mini_init(&i, &is_exit, &is_collect, &is_player);
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'E')
				is_exit = 1;
			if (map->map[i][j] == 'P')
				is_player++;
			if (map->map[i][j] == 'C')
				is_collect++;
			j++;
		}
		i++;
	}
	ft_mini_check(is_exit, is_collect, is_player);
	map->collect = is_collect;
}

void	ft_check_valid_map(t_map *map, char *path)
{
	ft_process_map(map, path);
	ft_check_width(map);
	if (map->length == map->width)
	{
		printf("map should be rectangular !!\n");
		exit(0);
	}
	ft_check_valid(map);
	ft_check_walls(map);
	ft_check_components(map);
	map->exit = 1;
}

void	get_player_pos(char **map, int *x, int *y)
{
	int i;
	int j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*x = i;
				*y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	ft_valid_move(char **map, int collect, int x, int y)
{

	if (map[x][y] == '0' || map[x][y] == 'C' || (map[x][y] == 'E' && !collect))
		return (1);
	return (0);
}

void	ft_move_player1(t_vars *vars, int x, int y, int *cp)
{
	printf("%d moves\n",++(*cp));
	mlx_put_image_to_window(vars->mlx, vars->win, vars->empty, 50 * y, 50 * x);
	vars->map->map[x][y] = '0';
}

void	ft_move_player2(t_vars *vars, int x, int y)
{
	if (vars->map->map[x][y] == 'C')
		vars->map->collect--;
	if (vars->map->map[x][y] == 'E')
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->empty, 50 * y, 50 * x);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->player, 50 * y, 50 * x);
	vars->map->map[x][y] = 'P';
}

void	ft_movments(t_vars *vars, int keypress, int x, int y)
{
	static int cp;

	if ((keypress == 2 || keypress == 124) && ft_valid_move(vars->map->map, vars->map->collect, x, y + 1))
	{
		ft_move_player1(vars, x , y, &cp);
		ft_move_player2(vars, x , y + 1);
	}
	if ((keypress == 0 || keypress == 123) && ft_valid_move(vars->map->map, vars->map->collect, x, y - 1))
	{
		ft_move_player1(vars, x , y, &cp);
		ft_move_player2(vars, x , y - 1);
	}
	if ((keypress == 13 || keypress == 126) && ft_valid_move(vars->map->map, vars->map->collect, x - 1, y))
	{
		ft_move_player1(vars, x , y, &cp);
		ft_move_player2(vars, x - 1, y);
	}
	if ((keypress == 1 || keypress == 125) && ft_valid_move(vars->map->map, vars->map->collect, x + 1, y))
	{
		ft_move_player1(vars, x , y, &cp);
		ft_move_player2(vars, x + 1, y);
	}
}

int	ft_key_events(int keypress, t_vars *vars)
{
	int	x;
	int	y;
	//esc 53 | w 13 | a 0 | d 2 | s 1 | up 126 | down 125 | right 124 | left 123
	get_player_pos(vars->map->map, &x, &y);
	if (keypress == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	ft_movments(vars, keypress, x, y);
	return (0);
}

int	ft_mouse_events(int keypress, t_vars *vars)
{
	//1 for LC | 2 for RC
	return (0);
}

void	ft_imgs_init(t_vars *vars, t_map *map)
{
	int	length;
	int	width;

	vars->wall = mlx_xpm_file_to_image(vars->mlx, "./assests/wall.xpm", &width, &length);
	vars->collect = mlx_xpm_file_to_image(vars->mlx, "./assests/collect1.xpm", &width, &length);
	vars->empty = mlx_xpm_file_to_image(vars->mlx, "./assests/floor.xpm", &width, &length);
	vars->player = mlx_xpm_file_to_image(vars->mlx, "./assests/player.xpm", &width, &length);
	vars->exit = mlx_xpm_file_to_image(vars->mlx, "./assests/exit1.xpm", &width, &length);
	vars->map = map;
}

void	ft_choose_img(t_vars vars, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(vars.mlx, vars.win, vars.wall, 50 * x, 50 * y);
	else{
		mlx_put_image_to_window(vars.mlx, vars.win, vars.empty, 50 * x, 50 * y);
		if (c == 'P')
		{
			mlx_put_image_to_window(vars.mlx, vars.win, vars.player, 50 * x, 50 * y);
		}
		if (c == 'C')
			mlx_put_image_to_window(vars.mlx, vars.win, vars.collect, 50 * x, 50 * y);
		if (c == 'E')
			mlx_put_image_to_window(vars.mlx, vars.win, vars.exit, 50 * x, 50 * y);
	}

}

void	ft_fill_window(t_map *map, t_vars vars)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			ft_choose_img(vars, map->map[i][j], j, i);
			j++;
		}
		i++;
	}
}

void	ft_gameplay(t_map *map)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 50 * map->width, 50 * map->length, "Hello world!");
	ft_imgs_init(&vars, map);
	ft_fill_window(map, vars);
	mlx_key_hook(vars.win, ft_key_events, &vars);
	mlx_mouse_hook(vars.win, ft_mouse_events, &vars);
	mlx_loop(vars.mlx);
}

int	main(int ac, char *av[])
{
	t_map	map;

	ft_check_args(ac, av);
	ft_check_valid_map(&map, av[1]);
	ft_gameplay(&map);
	//ft_affiche(map.map);
}
