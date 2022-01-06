/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:56:22 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/06 18:07:35 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_get_path(char *cmd, char *path)
{
	char	**tmp;
	char	*sub;
	char	*join;
	char	*test;
	int		i;

	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	sub = ft_substr(path, 5, 1000);
	tmp = ft_split(sub, ':');
	free(sub);
	i = 0;
	while (tmp[i])
	{
		join = ft_strjoin(tmp[i], "/");
		test = ft_strjoin(join, cmd);
		free(join);
		if (!access(test, F_OK))
			return (free_tab(tmp), test);
		free (test);
		i++;
	}
	return (free_tab(tmp), NULL);
}

t_cmds	*ft_new_node(char *str, char *path)
{
	t_cmds	*new;

	new = (t_cmds *)malloc(sizeof(t_all));
	if (!new)
		return (NULL);
	new->cmd = ft_split(str, ' ');
	new->path = ft_get_path(new->cmd[0], path);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	if (!new)
		return ;
	if (!lst[0])
	{
		lst[0] = new;
		return ;
	}
	tmp = lst[0];
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	free_list(t_cmds *lst)
{
	while (lst)
	{
		if (lst->cmd)
			free_tab(lst->cmd);
		if (lst->path)
			free(lst->path);
		if (lst)
			free(lst);
		lst = lst->next;
	}
}
