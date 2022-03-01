/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:38:33 by hdrabi            #+#    #+#             */
/*   Updated: 2022/02/22 11:30:12 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*ft_death(void *p)
{
	t_philo	*philo;
	t_all	*all;

	philo = (t_philo *)p;
	all = philo->all;
	while (1)
	{
		if (ft_time_diff(ft_timestamp(), philo->last_meal) > all->death_timer)
		{
			ft_print(all, philo->_id, "died");
			sem_wait(all->writing);
			all->philo_dead = 1;
			exit(1);
		}
		usleep(50);
		if (philo->is_full == all->meal_cp)
			all->all_full++;
		if (all->all_full == all->philo_cp)
		{
			all->philo_dead = 1;
			exit(0);
		}
	}
	return ((void *)0);
}

void	ft_eats(t_all *all, t_philo *philo)
{
	sem_wait(all->forks);
	ft_print(all, philo->_id, "has taken a fork");
	sem_wait(all->forks);
	ft_print(all, philo->_id, "has taken a fork");
	ft_print(all, philo->_id, "is eating");
	philo->last_meal = ft_timestamp();
	ft_sleep(all, all->eating_timer);
	philo->is_full++;
	sem_post(all->forks);
	sem_post(all->forks);
	ft_print(all, philo->_id, "is sleeping");
	ft_sleep(all, all->sleep_timer);
	ft_print(all, philo->_id, "is thinking");
}

void	ft_start(t_philo *philo, t_all *all)
{
	pthread_t	death;

	philo->last_meal = ft_timestamp();
	if (pthread_create(&death, NULL, &ft_death, philo))
		exit(ft_putstr("Error : Failed To Create Thread!!", 1));
	if (philo->_id % 2)
		usleep(150000);
	while (!all->philo_dead)
		ft_eats(all, philo);
	pthread_detach(death);
}

void	ft_exit(t_all *all)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < all->philo_cp)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (all->head)
			{
				kill(all->head->philo, SIGTERM);
				if (all->head->next == all->_first)
					break ;
				all->head = all->head->next;
			}
			break ;
		}
	}
	sem_close(all->forks);
	sem_close(all->writing);
	sem_unlink("forks");
	sem_unlink("writing");
	ft_free_list(all);
}

void	ft_exec(t_all *all)
{
	int	i;

	all->ground0 = ft_timestamp();
	i = 0;
	while (++i <= all->philo_cp)
	{
		all->head->philo = fork();
		if (all->head->philo < 0)
			exit(ft_putstr("Error : Forking Failed !!", 1));
		if (all->head->philo == 0)
			ft_start(all->head, all);
		usleep(50);
		all->head = all->head->next;
	}
	ft_exit(all);
}
