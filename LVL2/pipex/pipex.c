/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 11:11:20 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/18 13:53:25 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char *av[], char *env[])
{
	t_all	all;

	if (!env[0])
		ft_error("Error : env");
	if (ac != 5)
		ft_error("Error : wrong number of arguments");
	ft_parse_args(&all, av, ac - 1, env);
	ft_exec(all, env);
	free_list(all.head);
	return (0);
}
