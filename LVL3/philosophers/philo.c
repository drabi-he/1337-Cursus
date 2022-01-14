/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:50:25 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/14 14:14:55 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

typedef struct s_philo
{
	int				_id;
	pthread_t		philo;
	pthread_mutex_t	fork;
	size_t			last_meal;
	int				is_full;
	struct s_all	*all;
	struct s_philo	*next;
}	t_philo;

typedef struct s_all
{
	int				philo_cp;
	t_philo			*_first;
	t_philo			*head;
	size_t			death_timer;
	size_t			sleep_timer;
	size_t			eating_timer;
	size_t			meal_cp;
	int				philo_dead;
	size_t			ground0;
	int				all_full;
}	t_all;

//utils
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr(char *str, int error)
{
	if (str)
		write(1, str, strlen(str));
	return (error);
}

size_t	ft_timestamp(void)
{
	struct timeval	_t;

	gettimeofday(&_t, NULL);
	return (_t.tv_sec * 1000 + _t.tv_usec / 1000);
}

size_t	ft_time_diff(size_t current, size_t past)
{
	return (current - past);
}

void	ft_print(t_all *all, int _id, char *str)
{
	if (!all->philo_dead)
		printf ("%10zu ms %3d %s\n",
			ft_time_diff(ft_timestamp(), all->ground0), _id, str);
}

void	ft_sleep(t_all *all, size_t time)
{
	if (!all->philo_dead)
		usleep(time * 1000);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	rst;

	i = 0;
	sign = 1;
	rst = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == '\t' )
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		rst = rst * 10 + str[i] - '0';
		i++;
	}
	return (sign * rst);
}

t_philo	*ft_new_node(int _id, t_all *all)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->_id = _id;
	new->last_meal = 0;
	new->is_full = 0;
	if (pthread_mutex_init(&new->fork, NULL))
		ft_putstr("Error : Failed to initialize mutex\n", 1);
	new->all = all;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*cp;

	if (!new)
		return ;
	if (!lst[0])
	{
		lst[0] = new;
		new->next = new;
		return ;
	}
	cp = lst[0];
	while (cp->next != lst[0])
		cp = cp->next;
	cp->next = new;
	new->next = lst[0];
}

void	ft_free_list(t_all *all)
{
	int	i;

	i = 0;
	while (++i <= all->philo_cp)
	{
		pthread_mutex_destroy(&all->head->fork);
		free(all->head);
		all->head = all->head->next;
	}
}

//parsing
int	ft_check_digits(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (!ft_isdigit(av[i][j]))
				return (1);
	}
	return (0);
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
	all->ground0 = ft_timestamp();
	all->all_full = 0;
	i = 0;
	all->head = NULL;
	while (++i <= all->philo_cp)
		ft_lstadd_back(&all->head, ft_new_node(i, all));
	all->_first = all->head;
	return (0);
}

void	ft_eats(t_all *all, t_philo *philo)
{
		pthread_mutex_lock(&philo->fork);
		ft_print(all, philo->_id, "has taken a fork");
		pthread_mutex_lock(&philo->next->fork);
		ft_print(all, philo->_id, "has taken a fork");
		ft_print(all, philo->_id, "is eating");
		philo->last_meal = ft_timestamp();
		philo->is_full++;
		ft_sleep(all, all->eating_timer);
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
		usleep(1000);
	while (!all->philo_dead)
		ft_eats(all, current);
	return (0);
}

void	ft_dead(t_all *all, t_philo *philo)
{
	int i = 0;

	while (philo)
	{
		if (ft_time_diff(ft_timestamp(), philo->last_meal) > all->death_timer)
		{
			ft_print(all, philo->_id, "died");
			all->philo_dead = 1;
			break ;
		}
		if (all->all_full == all->philo_cp)
		{
			all->philo_dead = 1;
		}
		philo = philo->next;
	}
}

//exec
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

int	main(int ac, char *av[])
{
	t_all	all;

	if (ac < 5 || ac > 6)
		return(ft_putstr("Error : Wrong Number Of Arguments!!\n", 1));
	if (ft_parse_args(&all, av))
		return (ft_putstr("Error : Wrong Arguments Format!!\n", 1));
	if (ft_exec(&all))
		return(ft_putstr("Error : failed to create thread!!\n", 1));
	//while (!all.philo_dead);
	// t_philo	*tmp;
	// tmp = all.head;
	// while (tmp)
	// {
	// 	printf("philo %d\n",tmp->_id);
	// 	tmp = tmp->next;
		//usleep(100000);
	// }
	return (0);
}

