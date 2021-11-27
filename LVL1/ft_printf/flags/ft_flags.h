/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 16:27:53 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/27 17:26:47 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FLAGS_H
# define FT_FLAGS_H
# include <stdarg.h>
# include <stdlib.h>

typedef struct s_print
{
	void			*portion;
	void			*flags;
	int				width;
	int				is_p;
	int				precision;
	char			conversion;
	struct s_print	*next;
}	t_print;

t_print *ft_devide(const char *str);
t_print	*ft_create_lst(t_print **lst, const char *str);
int ft_check_flags(char c);
int ft_check_conversion(char c);
t_print *ft_new_node(char *str, char *flags,int width, char conversion,int is_p,int precision);
t_print	*ft_check_all(const char *str, int *start, char *portion, int is_p);
int	ft_check_valid (t_print *lst);
int	ft_strcmp(char *s1, char *s2);
void free_all(t_print *lst);
void ft_get_results(t_print *lst, va_list args, int *len);
void	ft_print_char(char *flag,int width, char c, int *len);
void	ft_print_str(char *flag,int is_p,int prcision,int width, char *c, int *len);
void	ft_print_ptr(char *flag,int is_p,int precision, int width, size_t addr, int *len);
void	ft_print_all(char	*str,int *len);
void	ft_putnbr_base(size_t nbr, int form , int *l);
#endif
