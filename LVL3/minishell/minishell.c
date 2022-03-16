/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:05:24 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/16 18:37:05 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(t_tree *root)
{
	if (!root)
		return ;
	if (root->ifd > 0)
		close(root->ifd);
	if (root->ofd > 0)
		close(root->ofd);
	ft_close_fd(root->right);
	ft_close_fd(root->left);
	if (!access(".tmp", F_OK))
		unlink(".tmp");
}

void	ft_exit(void)
{
	printf("exit\n");
	exit(0);
}

int	ft_get_list_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**ft_list_to_array(void)
{
	int		len;
	int		i;
	t_env	*tmp;
	char	**t;

	len = ft_get_list_size(g_all.env_head);
	t = (char **)malloc((len + 1) * sizeof(char *));
	if (!t)
		return (NULL);
	tmp = g_all.env_head;
	i = 0;
	while (tmp)
	{
		t[i] = ft_strjoin(ft_strdup(tmp->key), ft_strdup("="));
		t[i] = ft_strjoin(t[i], ft_strdup(tmp->value));
		i++;
		tmp = tmp->next;
	}
	return (t);
}

int	main(int ac, char *av[], char *env[])
{
	char	*str;

	(void)av;
	ft_env_init(&g_all.env_head, env);
	while (1)
	{
		g_all.status_s = 0;
		str = readline("\033[0;33m\e[1mMiniShell--> \e[0m\033[0m");
		if (!str)
			return (printf("Exit\n"), 1);
		add_history(str);
		if (ft_check_syntax(str) || !ft_strcmp(str, "\0"))
		{
			free (str);
			continue ;
		}
		g_all.status_s = 1;
		ft_tree_init(str);
		free(str);
		ft_close_fd(g_all.root);
		ft_free_garbage(g_all.g_head);
	}
	ft_free_env();
	return (ac);
}
