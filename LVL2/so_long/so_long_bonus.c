/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 11:54:10 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/30 13:10:38 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "mlx.h"

typedef struct s_vars
{
	char	**map;
	int		length;
	int		width;
	int		collect;
	int		exit;
	int		cp;
	int		gameOver;
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_collect[8];
	void	*img_floor;
	void	*img_enemy;
	void	*img_exit[6];
	void	*img_player;
}	t_vars;

//mini utils
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
	int	i;

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

//map check utils
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

void	ft_check_width(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->map[i])
	{
		if ((int)ft_strlen(vars->map[i]) != vars->width)
		{
			printf("all line should have the same width !!\n");
			exit(0);
		}
		i++;
	}
}

void	ft_check_valid(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '0'
				&& map[i][j] != 'C' && map[i][j] != 'P'
				&& map[i][j] != 'E' && map[i][j] != 'F')
			{
				printf("invalid component found !!\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void	ft_check_walls(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if ((vars->map[i][j] != '1' && (i == 0 || i == vars->length - 1))
				|| ((vars->map[i][0] != '1' || vars->map[i][vars->width -1] != '1')
				&& (i != 0 || i != vars->length - 1)))
			{
				printf("Walls error !!\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

void	ft_process_map(t_vars *vars, char *path)
{
	int	fd;
	int	length;
	int	i;

	length = ft_get_lines(path);
	vars->map = (char **)malloc((length + 1) * sizeof(char *));
	fd = open(path, O_RDONLY);
	if (fd < 3)
	{
		printf("file not found or permission denied !!\n");
		exit(0);
	}
	i = 0;
	while (i < length)
	{
		vars->map[i] = get_next_line(fd);
		i++;
	}
	vars->length = length;
	vars->width = ft_strlen(vars->map[0]);
	vars->map[i] = 0;
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

void	ft_check_components(t_vars *vars)
{
	int	i;
	int	j;
	int	is_exit;
	int	is_collect;
	int	is_player;

	ft_mini_init(&i, &is_exit, &is_collect, &is_player);
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'E')
				is_exit = 1;
			if (vars->map[i][j] == 'P')
				is_player++;
			if (vars->map[i][j] == 'C')
				is_collect++;
			j++;
		}
		i++;
	}
	ft_mini_check(is_exit, is_collect, is_player);
	vars->collect = is_collect;
	vars->exit = 0;
}

// map check
void	ft_check_args(int ac, char **av)
{
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

void	ft_check_valid_map(t_vars *vars, char *path)
{
	ft_process_map(vars, path);
	ft_check_width(vars);
	if (vars->length == vars->width)
	{
		printf("map should be rectangular !!\n");
		exit(0);
	}
	ft_check_valid(vars->map);
	ft_check_walls(vars);
	ft_check_components(vars);
}

//gameplay and display
// init images and fill window
void	ft_collect_img(t_vars *vars, int *cord)
{
	vars->img_collect[0] = mlx_xpm_file_to_image(vars->mlx, "./assests/box1.xpm", &cord[0], &cord[1]);
	vars->img_collect[1] = mlx_xpm_file_to_image(vars->mlx, "./assests/box2.xpm", &cord[0], &cord[1]);
	vars->img_collect[2] = mlx_xpm_file_to_image(vars->mlx, "./assests/box3.xpm", &cord[0], &cord[1]);
	vars->img_collect[3] = mlx_xpm_file_to_image(vars->mlx, "./assests/box4.xpm", &cord[0], &cord[1]);
	vars->img_collect[4] = mlx_xpm_file_to_image(vars->mlx, "./assests/box5.xpm", &cord[0], &cord[1]);
	vars->img_collect[5] = mlx_xpm_file_to_image(vars->mlx, "./assests/box6.xpm", &cord[0], &cord[1]);
	vars->img_collect[6] = mlx_xpm_file_to_image(vars->mlx, "./assests/box7.xpm", &cord[0], &cord[1]);
	vars->img_collect[7] = mlx_xpm_file_to_image(vars->mlx, "./assests/box8.xpm", &cord[0], &cord[1]);
}

void	ft_door_img(t_vars *vars, int *cord)
{
	vars->img_exit[0] = mlx_xpm_file_to_image(vars->mlx, "./assests/door1.xpm", &cord[0], &cord[1]);
	vars->img_exit[1] = mlx_xpm_file_to_image(vars->mlx, "./assests/door2.xpm", &cord[0], &cord[1]);
	vars->img_exit[2] = mlx_xpm_file_to_image(vars->mlx, "./assests/door3.xpm", &cord[0], &cord[1]);
	vars->img_exit[3] = mlx_xpm_file_to_image(vars->mlx, "./assests/door4.xpm", &cord[0], &cord[1]);
	vars->img_exit[4] = mlx_xpm_file_to_image(vars->mlx, "./assests/door5.xpm", &cord[0], &cord[1]);
	vars->img_exit[5] = mlx_xpm_file_to_image(vars->mlx, "./assests/door6.xpm", &cord[0], &cord[1]);
}

void	ft_vars_init(t_vars *vars)
{
	int cord[2];

	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 50 * vars->width, 50 * vars->length, "So Long");
	vars->cp = 0;
	vars->img_wall = mlx_xpm_file_to_image(vars->mlx, "./assests/wall.xpm", &cord[0], &cord[1]);
	vars->img_floor = mlx_xpm_file_to_image(vars->mlx, "./assests/floor.xpm", &cord[0], &cord[1]);
	vars->img_player = mlx_xpm_file_to_image(vars->mlx, "./assests/playerR.xpm", &cord[0], &cord[1]);
	vars->img_enemy = mlx_xpm_file_to_image(vars->mlx, "./assests/enemy.xpm", &cord[0], &cord[1]);
	ft_collect_img(vars, cord);
	ft_door_img(vars, cord);
	vars->gameOver = 0;
}

void	ft_choose_img(t_vars vars, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(vars.mlx, vars.win, vars.img_wall, 50 * x, 50 * y);
	else{
		mlx_put_image_to_window(vars.mlx, vars.win, vars.img_floor, 50 * x, 50 * y);
		if (c == 'P')
		{
			mlx_put_image_to_window(vars.mlx, vars.win, vars.img_player, 50 * x, 50 * y);
		}
		if (c == 'C')
			mlx_put_image_to_window(vars.mlx, vars.win, vars.img_collect[0], 50 * x, 50 * y);
		if (c == 'E' && (vars.collect || vars.exit))
			mlx_put_image_to_window(vars.mlx, vars.win, vars.img_exit[0], 50 * x, 50 * y);
		if (c == 'E' && !vars.exit && !vars.collect)
			mlx_put_image_to_window(vars.mlx, vars.win, vars.img_exit[5], 50 * x, 50 * y);
		if (c == 'F')
			mlx_put_image_to_window(vars.mlx, vars.win, vars.img_enemy, 50 * x, 50 * y);
	}

}

void	ft_fill_window(t_vars vars)
{
	int	i;
	int	j;

	i = 0;
	while (vars.map[i])
	{
		j = 0;
		while (vars.map[i][j])
		{
			ft_choose_img(vars, vars.map[i][j], j, i);
			j++;
		}
		i++;
	}
}

//movments
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

	if (map[x][y] == '0' || map[x][y] == 'C' || (map[x][y] == 'E' && !collect) || map[x][y] == 'F')
		return (1);
	return (0);
}

void	ft_gameover(t_vars *vars)
{
	if(vars->gameOver == 1)
	{
		mlx_clear_window(vars->mlx, vars->win);
		ft_fill_window(*vars);
		mlx_destroy_window(vars->mlx, vars->win);
		exit (0);
	}
}

void	ft_dead(t_vars *vars, char c)
{
	int	x;
	int	y;

	ft_gameover(vars);
	if (c == 'F')
	{
		mlx_destroy_image(vars->mlx, vars->img_player);
		mlx_clear_window(vars->mlx, vars->win);
		vars->img_player = mlx_xpm_file_to_image(vars->mlx, "./assests/dead.xpm", &x, &y);
		vars->gameOver = 1;
		ft_fill_window(*vars);
		printf("you lose !!\n");
	}
}

void	ft_collect_exit(t_vars *vars, int x, int y, int move)
{
	if (move == 1 )
		y++;
	if (move == 2)
		y--;
	if (move == 3)
		x--;
	if (move == 4)
		x++;
	if (vars->map[x][y] == 'C')
	{
		vars->collect--;
		if (vars->collect == 0)
		vars->exit = 1;
	}
	if (vars->map[x][y] == 'E')
	{
		sleep(1);
		printf("you won!!\n");
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	ft_dead(vars, vars->map[x][y]);
}

void	ft_player_img(t_vars *vars, int x, int y, int move)
{
	if (vars->gameOver == 1)
		return ;
	if (move == 1 )
	{
		vars->map[x][++y] = 'P';
		vars->img_player = mlx_xpm_file_to_image(vars->mlx, "./assests/playerR.xpm", &x, &y);
	}
	if (move == 2)
	{
		vars->map[x][--y] = 'P';
		vars->img_player = mlx_xpm_file_to_image(vars->mlx, "./assests/playerL.xpm", &x, &y);
	}
	if (move == 3)
	{
		vars->map[--x][y] = 'P';
		vars->img_player = mlx_xpm_file_to_image(vars->mlx, "./assests/playerU.xpm", &x, &y);
	}
	if (move == 4)
	{
		vars->map[++x][y] = 'P';
		vars->img_player = mlx_xpm_file_to_image(vars->mlx, "./assests/playerD.xpm", &x, &y);
	}
}

void	ft_move_player(t_vars *vars, int x, int y, int move)
{
	ft_collect_exit(vars, x, y, move);
	if (vars->gameOver == 1)
		return ;
	printf("%d moves\n",++(vars->cp));
	vars->map[x][y] = '0';
	mlx_destroy_image(vars->mlx,vars->img_player);
	ft_player_img(vars, x, y, move);
}

void	ft_movments(t_vars *vars, int keypress, int x, int y)
{
	if ((keypress == 2 || keypress == 124) && ft_valid_move(vars->map, vars->collect, x, y + 1))
		ft_move_player(vars, x , y, 1);
	if ((keypress == 0 || keypress == 123) && ft_valid_move(vars->map, vars->collect, x, y - 1))
		ft_move_player(vars, x , y, 2);
	if ((keypress == 13 || keypress == 126) && ft_valid_move(vars->map, vars->collect, x - 1, y))
		ft_move_player(vars, x , y, 3);
	if ((keypress == 1 || keypress == 125) && ft_valid_move(vars->map, vars->collect, x + 1, y))
		ft_move_player(vars, x , y, 4);
	mlx_clear_window(vars->mlx, vars->win);
	ft_fill_window(*vars);
}

int	ft_key_events(int keypress, t_vars *vars)
{
	int	x;
	int	y;
	//esc 53 | w 13 | a 0 | d 2 | s 1 | up 126 | down 125 | right 124 | left 123
	get_player_pos(vars->map, &x, &y);
	if (keypress == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	ft_movments(vars, keypress, x, y);
	return (0);
}

void	ft_anim_collect(t_vars *vars, int k)
{
	int i;
	int j;

	i = 0;
	if (!vars->collect)
		return ;
	usleep(80000);
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img_collect[k], 50 * j, 50 * i);
			j++;
		}
		i++;
	}
}

void	ft_anim_door(t_vars *vars, int k)
{
	int i;
	int j;

	i = 0;
	usleep(80000);
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->img_exit[k], 50 * j, 50 * i);
			j++;
		}
		i++;
	}
}

int anim(t_vars *vars)
{
	static int	k;
	static int	j;

	while(1)
	{
		ft_anim_collect(vars, k);
		k++;
		if (k == 8)
			k = 0;
		if (vars->exit == 1)
		{
			if (j < 6)
				ft_anim_door(vars, j);
			else
				vars->exit = 0;
			j++;
		}

		break ;
	}
	return (0);
}

int	ft_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

void	ft_gameplay(t_vars *vars)
{
	ft_vars_init(vars);
	ft_fill_window(*vars);
	mlx_key_hook(vars->win, ft_key_events, vars);
	mlx_hook(vars->win, 17, 0, ft_close, &vars);
	mlx_loop_hook(vars->mlx, anim,vars);
	mlx_loop(vars->mlx);
}

int	main(int ac, char *av[])
{
	t_vars	vars;

	ft_check_args(ac, av);
	ft_check_valid_map(&vars, av[1]);
	ft_gameplay(&vars);
}
