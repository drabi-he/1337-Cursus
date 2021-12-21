/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verfiy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 10:58:25 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/21 11:00:35 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ft_check_input_type(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]) || (args[i][j] == '-' && (j != 0
				|| !ft_isdigit(args[i][j + 1]))))
			{
				write(1, "Error\n", 6);
				exit(0);
			}
			j++;
		}
		i++;
	}
}

static void	ft_check_double(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = i + 1;
		while (args[j])
		{
			if (!ft_strcmp(args[i], args[j]))
			{
				write(1, "Error\n", 6);
				exit(0);
			}
			j++;
		}
		i++;
	}
}

static t_stack	*ft_fill_stack(char **args)
{
	t_stack	*tmp;
	t_stack	*list;
	int		i;

	list = NULL;
	i = 0;
	while (args[i])
	{
		tmp = ft_new_node(ft_atoi(args[i]));
		if (!tmp)
			return (NULL);
		ft_lstadd_back(&list, tmp);
		i++;
	}
	free (args);
	return (list);
}

t_stack	*ft_devide_args(char **args)
{
	ft_check_input_type(args);
	ft_check_double(args);
	return (ft_fill_stack(args));
}
