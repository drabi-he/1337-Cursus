/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:26:30 by hdrabi            #+#    #+#             */
/*   Updated: 2021/11/19 11:28:26 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_line
{
	void			*portion;
	struct s_line	*next;
}				t_line;

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strchr(const char *str, int n);
t_line	*ft_lstnew(void *content);
char	*get_next_line(int fd);
char	*get_line(t_line **list, t_line *last, size_t len, int fd);
char	*join_list(t_line **list, size_t len_rd, size_t len);
void	convert_list(t_line **list, size_t total_len, char *result);

#endif
