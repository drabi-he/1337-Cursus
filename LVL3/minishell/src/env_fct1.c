/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_fct1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:09:51 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/16 18:31:44 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_add_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

int	ft_env_split(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	ft_free_env(void)
{
	while (g_all.env_head)
	{
		free(g_all.env_head->key);
		if (g_all.env_head->value)
			free(g_all.env_head->value);
		free (g_all.env_head);
		g_all.env_head = g_all.env_head->next;
	}
}

void	ft_edit_env(t_env *env, char *key, char *new_val)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (tmp)
				free(tmp->value);
			tmp->value = ft_strdup(new_val);
			return ;
		}
		tmp = tmp->next;
	}
	if (key)
		ft_add_env(&tmp, ft_new_env(ft_strdup(key), ft_strdup(new_val)));
}
