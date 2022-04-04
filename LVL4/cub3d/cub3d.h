/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:49:16 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/04 20:23:08 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define SCREEN_W 1024
# define SCREEN_H 720
# define MOVE_SPEED 1
# define ROT_SPEED 0.05
# define T_W 64
# define T_H 64
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define WHITE 0xFFFFFF
# define YELLOW 0xFFFF00

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		sl;
	int		en;
}	t_texture;

typedef struct s_ray
{
	float			pos_x;
	float			pos_y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			camera;
	float			ray_dir_x;
	float			ray_dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	float			wall_dist;
	int				hit;
	int				side;
	unsigned int	color;
	float			old_pos_x;
	float			old_plane_x;
	int				line_height;
	int				draw_start;
	int				draw_end;
	t_texture		t[8];
	unsigned int	**buffer;
	int				tex_num;
	float			wall_x;
	int				tex_x;
	int				tex_y;
	float			tex_pos;
	float			step;
}	t_ray;

typedef struct s_info
{
	int	i_end;
	int	j_end;
	int	i_start;
	int	j_start;
	int	height;
	int	width;
}	t_info;

typedef struct s_win
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	void	*mini;
	void	*addr_mini;
	int		bpp;
	int		sl;
	int		en;
	int		x;
	t_info	info;
}	t_win;

typedef struct s_all
{
	t_win	win;
	t_ray	ray;
	char	**map;
	int		max_width;
	int		max_height;
}	t_all;

//mini_utils
size_t	ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strdup(char *s1);
char	*get_next_line(int fd);

//mini_utils_2
char	*ft_strchr(char *s, int c);
void	pixel_put(t_win *win, int x, int y, int color);
void	pixel_put_mini(t_win *win, int x, int y, int color);
void	ft_verline(t_win *win, unsigned int **buffer, int mode);
float	f_abs(float n);

//error_handles
void	ft_error(char *str, int exit_status);

//map_check
void	read_map(t_all *all, char *str);
void	check_walls(t_all *all);

//gameplay
void	ray_init(t_ray	*ray, char **map);
void	vars_init(t_ray *ray, int x);
void	initial_dist(t_ray *ray);
void	wall_collision(t_ray *ray, char **map);
void	draw_mini_map(t_ray *ray, t_win *win, char **map);
void	draw_screen(t_ray *ray, t_win *win, char **map);
int		key_press(int key, t_all *all);
void	gameplay(t_all *all);

void	print_ray(t_ray *ray);

#endif
