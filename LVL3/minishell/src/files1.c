/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 15:49:40 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/19 18:26:32 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc(char *limiter, int fd)
{
	char	*hdoc;

	while (1)
	{
		g_all.status_s = 0;
		hdoc = readline("\033[0;31mheredoc>\033[0m ");
		if (!hdoc)
			return ;
		hdoc = ft_parse_dollar(hdoc, 1);
		if (!ft_strcmp(limiter, hdoc))
			break ;
		write (fd, hdoc, ft_strlen(hdoc));
		write (fd, "\n", 1);
	}
}

char	*ft_get_herdoc(char *str, int i, t_tree **node)
{
	char	*left;
	char	*right;
	char	*rst;
	int		j;

	j = i;
	while (str[j] && str[j] == ' ')
		j++;
	while (str[j] && (str[j] != ' ' && str[j] != '<' && str[j] != '>'))
		j++;
	node[0]->infile = ft_strtrim(ft_substr2(str, i, j - i), " ");
	if (!node[0]->infile)
		return (printf("MiniShell: syntax error\n"), NULL);
	node[0]->ifd = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_heredoc(node[0]->infile, node[0]->ifd);
	left = ft_substr(str, 0, i - 2);
	right = ft_substr(str, j, ft_strlen(str));
	rst = ft_strjoin2(left, right);
	free(left);
	free(right);
	close(node[0]->ifd);
	node[0]->ifd = open(".tmp", O_RDONLY, 0644);
	return (rst);
}

char	*ft_get_infile(char *str, int i, t_tree **node)
{
	char	*left;
	char	*right;
	char	*rst;
	int		j;

	j = i;
	while (str[j] && str[j] == ' ')
		j++;
	while (str[j] && (str[j] != ' ' && str[j] != '<' && str[j] != '>'))
		j++;
	node[0]->infile = ft_strtrim(ft_substr2(str, i, j - i), " ");
	if (!node[0]->infile)
		return (printf("MiniShell: syntax error\n"), NULL);
	if (access(node[0]->infile, F_OK | R_OK))
	{
		ft_print_error("MiniShell: ", node[0]->infile, \
			": file doesn't exist or permission denied!\n");
	}
	node[0]->ifd = open(node[0]->infile, O_RDONLY, 0644);
	left = ft_substr(str, 0, i - 1);
	right = ft_substr(str, j, ft_strlen(str));
	rst = ft_strjoin2(left, right);
	free(left);
	free(right);
	return (rst);
}

void	ft_split_red_mini(t_tree **node, char **str, int *i)
{
	(*i)++;
	if (str[0][*i] == '<')
	{
		(*i)++;
		str[0] = ft_get_herdoc(str[0], *i, node);
	}
	else
		str[0] = ft_get_infile(str[0], *i, node);
	(*i) = 0;
}

void	ft_split_red(char **str, t_tree **node)
{
	int	i;

	i = 0;
	while (str[0] && str[0][i])
	{
		ft_skip_quote(str[0], &i);
		if (str[0][i] == '<')
			ft_split_red_mini(node, str, &i);
		else if (str[0][i] == '>')
		{
			i++;
			if (str[0][i] == '>')
			{
				i++;
				str[0] = ft_get_a_outfile(str[0], i, node);
			}
			else
				str[0] = ft_get_outfile(str[0], i, node);
			i = 0;
		}
		else
			i++;
	}
}
