/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 17:08:31 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/16 10:50:12 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_outfile(char *str, int i, t_tree **node)
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
	node[0]->outfile = ft_strtrim(ft_substr2(str, i, j - i), " ");
	if (!access(node[0]->outfile, F_OK) && access(node[0]->outfile, W_OK))
	{
		printf("MiniShell: %s: permission denied!\n", node[0]->outfile);
	}
	node[0]->ofd = open(node[0]->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	left = ft_substr(str, 0, i - 1);
	right = ft_substr(str, j, ft_strlen(str));
	rst = ft_strjoin2(left, right);
	free (left);
	free (right);
	return (rst);
}

char	*ft_get_a_outfile(char *str, int i, t_tree **node)
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
	node[0]->outfile = ft_strtrim(ft_substr2(str, i, j - i), " ");
	if (!access(node[0]->outfile, F_OK) && access(node[0]->outfile, W_OK))
	{
		printf("MiniShell: %s: permission denied!\n", node[0]->outfile);
	}
	node[0]->ofd = open(node[0]->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	left = ft_substr(str, 0, i - 2);
	right = ft_substr(str, j, ft_strlen(str));
	rst = ft_strjoin2(left, right);
	free (left);
	free (right);
	return (rst);
}
