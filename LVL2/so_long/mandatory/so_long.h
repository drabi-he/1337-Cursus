/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 10:37:01 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/31 11:27:16 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "mlx.h"

typedef struct s_vars
{
	char	**map;
	int		length;
	int		width;
	int		collect;
	int		exit;
	int		cp;
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_collect;
	void	*img_floor;
	void	*img_exit[2];
	void	*img_player;
}	t_vars;

//mini utils
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strstr(char *str, char *to_find);
char	*get_next_line(int fd);

//check map
int		ft_get_lines(char *map);
void	ft_check_width(t_vars *vars);
void	ft_check_valid(char **map);
void	ft_check_walls(t_vars *vars);
void	ft_check_valid_map(t_vars *vars, char *path);

//keypress
int		ft_key_events(int keypress, t_vars *vars);
void	ft_collect_exit(t_vars *vars, int x, int y, int move);
int		ft_close(void);

//init
void	ft_vars_init(t_vars *vars);
void	ft_choose_img(t_vars vars, char c, int x, int y);
void	ft_fill_window(t_vars vars);
void	get_player_pos(char **map, int *x, int *y);
int		ft_valid_move(char **map, int collect, int x, int y);

//gfy norm
void	ft_gfy_norm(t_vars *vars, int x, int y, int move);

#endif