/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:24:12 by hdrabi            #+#    #+#             */
/*   Updated: 2022/02/21 11:30:53 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_time_diff(size_t current, size_t past)
{
	return (current - past);
}

void	ft_print(t_all *all, int _id, char *str)
{
	sem_wait(all->writing);
	if (!all->philo_dead)
		printf ("%10zu ms %3d %s\n",
			ft_time_diff(ft_timestamp(), all->ground0), _id, str);
	sem_post(all->writing);
}

void	ft_sleep(t_all *all, size_t time)
{
	if (!all->philo_dead)
		usleep(time * 1000);
}

void	ft_free_list(t_all *all)
{
	int	i;

	i = 0;
	while (++i <= all->philo_cp)
	{
		kill(all->head->philo, 15);
		free(all->head);
		all->head = all->head->next;
	}
	sem_close(all->forks);
	sem_close(all->writing);
	sem_unlink("forks");
	sem_unlink("writing");
	exit(0);
}

int	ft_parse_args(t_all *all, char **av)
{
	int	i;

	if (ft_check_digits(av))
		return (1);
	all->philo_cp = ft_atoi(av[1]);
	all->death_timer = ft_atoi(av[2]);
	all->eating_timer = ft_atoi(av[3]);
	all->sleep_timer = ft_atoi(av[4]);
	if (av[5])
		all->meal_cp = ft_atoi(av[5]);
	else
		all->meal_cp = -1;
	all->philo_dead = 0;
	all->all_full = 0;
	ft_sem_init(all);
	i = 0;
	all->head = NULL;
	while (++i <= all->philo_cp)
		ft_lstadd_back(&all->head, ft_new_node(i, all));
	all->_first = all->head;
	return (0);
}
