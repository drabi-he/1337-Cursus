/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 16:25:51 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/02 17:50:16 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLAGS_H
# define FT_FLAGS_H
# include "stdlib.h"
# include "stdio.h"
# include "stdarg.h"
# include "unistd.h"

typedef struct s_print
{
	char			*portion;
	char			*flags;
	int				width;
	int				is_p;
	int				precision;
	char			conversion;
	struct s_print	*next;
}	t_print;

//libft_utils
int		ft_isdigit(int c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(long long n, int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_print(size_t n, size_t size, int form, int *l);
void	ft_putnbr_base(size_t nbr, int form, int *l);
char	*ft_substr(const char *s, unsigned int start, size_t len);
ssize_t	ft_atoi(const char *str);

//ft_utils
void	free_all(t_print *lst);
int		ft_search_flag(char *flag, char c);
int		ft_ptr_null(int precision, int width, size_t addr);
int		ft_convert_len(size_t nb);
int		ft_nbr_len(long long nb);
int		ft_get_sp_count(int width, int precision, int nb_len, int nb);

//ft_devide_str
t_print	*ft_devide_str(const char *str);

//ft_check_all
t_print	*ft_check_all(const char *str, int *start, char *portion);

//ft_print_char
void	ft_print_char(t_print *node, char c, int *len);

//ft_print_str
void	ft_print_str(t_print *lst, char *str, int *len);

//ft_print_addr
void	ft_print_ptr(t_print *lst, size_t addr, int *len);

//ft_print_dec
void	ft_print_dec(t_print *lst, int nb, int *len);
void	ft_dec_extra(char *flag, int width, int nb, int *len);
void	ft_print_sign(char *flag, int nb);

//ft_print_un
void	ft_print_un(t_print *lst, unsigned int nb, int *len);
void	ft_un_extra(char *flags, int width, unsigned int nb, int *len);

//ft_print_hex
void	ft_print_hex(t_print *lst, size_t hex, int *len);
void	ft_hex_check(t_print *lst, size_t hex, int *len_print);

//ft_print_percent
void	ft_print_percent(t_print *lst, int *len);
#endif
