/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fct2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:20:05 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/15 17:59:43 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_env(t_env *head, char *search)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, search))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

static int	ft_get_list_size(t_env *env)
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

void	ft_free_env_array(char	**env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**ft_list_to_array(t_env *env)
{
	char	**exec_env;
	t_env	*tmp;
	int		len;
	int		i;

	if (!env)
		return (NULL);
	len = ft_get_list_size(env);
	exec_env = (char **)malloc((len + 1) * sizeof(char *));
	i = 0;
	tmp = env;
	while (tmp)
	{
		exec_env[i] = ft_strjoin(ft_strdup(tmp->key), ft_strdup("="));
		exec_env[i] = ft_strjoin(exec_env[i], ft_strdup(tmp->value));
		i++;
		tmp = tmp->next;
	}
	exec_env[i] = ft_strdup("\0");
	return (exec_env);
}

void	ft_env_init(t_env **env, char *s_env[])
{
	int	i;
	int	j;

	i = 0;
	env[0] = NULL;
	if (!s_env[0])
	{
		s_env = malloc(1 * sizeof(char *));
		s_env[0] = 0;
	}
	while (s_env[i])
	{
		j = ft_env_split(s_env[i]);
		ft_add_env(env, ft_new_env(ft_substr(s_env[i], 0, j), \
			ft_substr(s_env[i], j + 1, ft_strlen(s_env[i]))));
		i++;
	}
}
