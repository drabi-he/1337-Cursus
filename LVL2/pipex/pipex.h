/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:36:17 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/06 17:40:46 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_cmds
{
	char			**cmd;
	char			*path;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_all
{
	t_cmds	*head;
	int		p[2];
	int		fd[2];
	int		fork[2];
	char	*limiter;
}	t_all;

//utils
void	ft_putstr(char *str, int fd);
void	ft_error(char *msg);
size_t	ft_strlen(const char *s);
int		ft_strcmp(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
char	*get_next_line(int fd);
void	free_tab(char **t);
char	**ft_split(char const *s, char c);
char	*ft_get_path(char *cmd, char *path);
t_cmds	*ft_new_node(char *str, char *path);
void	ft_lstadd_back(t_cmds **lst, t_cmds *new);
void	free_list(t_cmds *lst);

//parsing
void	ft_fill_lst(t_cmds **lst, char **av, int ac, char *path);
char	*ft_get_path_line(char **env);
void	ft_parse_args(t_all *all, char **av, int ac, char **env);
void	ft_exec(t_all all, char **env);

//here_doc
void	ft_fill_lst2(t_cmds **lst, char **av, int ac, char *path);
void	ft_make_infile(t_all *all);
int		ft_parse_heredoc(t_all *all, char **av, int ac, char **env);
void	ft_exec2(t_all all, char **env);

#endif
