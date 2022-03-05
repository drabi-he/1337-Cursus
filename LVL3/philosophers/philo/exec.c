/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 15:28:52 by hdrabi            #+#    #+#             */
/*   Updated: 2022/03/05 15:03:22 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eats(t_all *all, t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	ft_print(all, philo->_id, "has taken a fork");
	pthread_mutex_lock(&philo->next->fork);
	ft_print(all, philo->_id, "has taken a fork");
	ft_print(all, philo->_id, "is eating");
	philo->last_meal = ft_timestamp();
	ft_sleep(all, all->eating_timer);
	philo->is_full++;
	if (philo->is_full == all->meal_cp)
		all->all_full++;
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
	ft_print(all, philo->_id, "is sleeping");
	ft_sleep(all, all->sleep_timer);
	ft_print(all, philo->_id, "is thinking");
}

void	*launch(void *philo)
{
	t_philo	*current;
	t_all	*all;

	current = (t_philo *)philo;
	all = current->all;
	if (current->_id % 2)
		usleep(100);
	while (!all->philo_dead)
		ft_eats(all, current);
	return (0);
}

void	ft_dead(t_all *all, t_philo *philo)
{
	while (philo)
	{
		if (ft_time_diff(ft_timestamp(), philo->last_meal) \
			> all->death_timer)
		{
			ft_print(all, philo->_id, "died");
			all->philo_dead = 1;
			return ;
		}
		if (all->all_full == all->philo_cp)
		{
			all->philo_dead = 1;
			return ;
		}
		usleep(1000);
		philo = philo->next;
	}
}

int	ft_exec(t_all *all)
{
	while (all->head)
	{
		if (pthread_create(&all->head->philo, NULL, &launch, all->head))
			return (1);
		all->head->last_meal = ft_timestamp();
		if (all->head->next == all->_first)
			break ;
		all->head = all->head->next;
	}
	all->head = all->head->next;
	ft_dead(all, all->head);
	return (0);
}
