/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 22:01:15 by hdrabi            #+#    #+#             */
/*   Updated: 2022/04/16 00:46:03 by hdrabi           ###   ########.fr       */
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

# define SCREEN_W 1280
# define SCREEN_H 720
# define X 0
# define Y 1
# define NO 0
# define SO 1
# define EA 2
# define WE 3
# define ROT_SPEED 0.1
# define MANDATORY 0
# define BONUS 1
# define T_W 64
# define T_H 64
# define U_DIV 1
# define V_DIV 1
# define V_MOVE 0.0

typedef struct s_sprite
{
	float	x;
	float	y;
	int		texture;
}	t_sprite;

typedef struct s_pair
{
	int		first;
	float	second;
}	t_pair;

typedef struct s_key
{
	int		w;
	int		a;
	int		s;
	int		d;
	int		l;
	int		r;
	float	move_speed;
	float	rot_speed;
}	t_key;

typedef struct s_parsing
{
	int		fd;
	int		index;
	int		counter;
	char	*tmpline;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_red;
	int		floor_green;
	int		floor_blue;
	int		color_floor;
	int		ceiling_red;
	int		ceiling_green;
	int		ceiling_blue;
	int		color_ceiling;
	char	**argv;
	char	*first_line;
	char	**map;
	size_t	count_lines;
	size_t	biggest_lines;
	size_t	skip_lines;
}	t_parsing;

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
	float			pos[2];
	float			dir[2];
	float			plane[2];
	float			camera;
	float			ray_dir[2];
	int				map[2];
	int				step[2];
	float			side_dist[2];
	float			delta_dist[2];
	float			wall_dist;
	int				hit;
	int				side;
	unsigned int	color;
	unsigned int	ceiling;
	unsigned int	floor;
	float			old_pos_x;
	float			old_plane_x;
	int				line_height;
	int				draw[2];
	t_texture		t[17];
	unsigned int	**buffer;
	float			*z_buffer;
	int				*sprit_order;
	float			*sprit_distance;
	t_sprite		*sprite;
	int				tex_num;
	float			wall_x;
	int				tex[2];
	float			tex_pos;
	float			steps;
	int				amount;
	float			spr[2];
	float			inv_det;
	float			transform[2];
	int				spr_screen;
	int				move_screen;
	int				spr_h;
	int				draw_y[2];
	int				spr_w;
	int				draw_x[2];
	int				anime;
	int				s;
}	t_ray;

typedef struct s_info
{
	int	end[2];
	int	start[2];
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
	int		mode;
	t_info	info;
}	t_win;

typedef struct s_all
{
	t_win		*win;
	t_ray		*ray;
	t_parsing	*parsing;
	char		**map;
	t_key		key;
}	t_all;

/*-------------------------------- MINI_UTILS --------------------------------*/
int				ft_error(char *str, int exit_status);
char			*ft_strchr(char *s, int c);
void			load_img(void *mlx, t_texture	*t, char *filename);
float			f_abs(float n);
void			print_instructions(t_key *key);
int				count_sprites(char **map);
int				ft_close(void);

/*-------------------------------- PARSING --------------------------------*/
void			*ft_memset(void *s, int c, size_t n);
void			replace_nl_with_null(char *str);
void			free_parsing(t_parsing *parsing);
int				ft_atoi(const char *str);
char			*ft_strdup(char *source);
int				check_file_name(char *str);
int				skip_spaces(char *tmpline);
int				assign_floor(t_parsing *parsing, int i);
int				assign_ceiling(t_parsing *parsing, int i);
int				assign_vars_two(t_parsing *parsing, int i);
int				assign_vars_three(t_parsing *parsing, int i);
int				assign_vars(t_parsing *parsing);
void			init_parsing(t_parsing *parsing, char *argv[]);
void			parsing_directions_colors_two(t_parsing *parsing);
int				parsing_directions_colors(t_parsing *parsing, \
						char *argv[], int argc);
int				skip_newlines(t_parsing *parsing);
void			parse_map(t_parsing *parsing, size_t i);
int				check_fist_last_line(t_parsing *parsing);
int				check_first_indexes(t_parsing *parsing);
int				check_map(t_parsing *parsing, int i, int j);
void			parse_map_assign_two(t_parsing *parsing, size_t *i);
void			parse_map_assign(t_parsing *parsing, size_t i);
void			replace_spc_wall(t_parsing *parsing);
int				search_for_player(t_parsing *parsing, int i, int j, int count);
int				search_for_player2(t_parsing *parsing, int i, int j, int count);
void			ft_bzero(void *s, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
int				contains_newline(char const *s1);
char			*first_line(char *str);
char			*second_part(char *str);
char			*get_next_line(int fd);
int				check_colors(char *str);
void			main_parse(int ac, char **av, t_parsing *parsing, int mode);

/*-------------------------------- INIT --------------------------------*/
void			vars_init(t_ray *ray, int x);
void			initial_dist(t_ray *ray);
void			wall_collision(t_ray *ray, char **map);
void			mini_check(t_ray *ray, char c);
void			initial_color(t_ray *ray);
void			initial_color_2(t_win *win, t_ray *ray);
void			init_all(t_all *all, t_parsing parsing, int mode);

/*-------------------------------- GRAPHICS --------------------------------*/
void			print_ray(t_ray *ray);
unsigned int	get_color(t_texture *t, int x, int y);
int				draw_mini_map(t_ray *ray, t_win *win, char **map);
void			draw_screen(t_ray *ray, t_win *win, char **map, int mode);
void			init_sprit_locations(t_sprite **sprite, char **map);
int				sprites(t_ray *ray, char **map);
int				scale_mini(t_win *win, float x, float y, int color);
void			choose_color(t_win *win, float x, float y, char c);
void			check_doors(char **map, float x, float y);
void			sort_sprites(int *order, float *dist, int amount);

/*-------------------------------- MOVEMENTS --------------------------------*/
int				key_press(int keycode, t_all *all);
int				key_release(int keycode, t_all *all);
int				smooth_move(t_all *all);
int				ft_move(int x, int y, t_all *all);
int				key_press(int key, t_all *all);

#endif