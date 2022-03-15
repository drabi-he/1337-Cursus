/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:05:24 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/15 15:14:42 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *env[])
{
	char	*str;

	(void)av;
	ft_env_init(&g_all.env_head, env);
	g_all.env = ft_list_to_array(g_all.env_head);
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
		ft_free_garbage(g_all.g_head);
	}
	ft_free_env(g_all.env_head);
	ft_free_env_array(g_all.env);
	return (ac);
}
