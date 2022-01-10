/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:50:25 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/10 17:37:15 by hdrabi           ###   ########.fr       */
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
	int				state;
	pthread_mutex_t	fork;
	suseconds_t		last_meal;
	struct s_philo	*next;
}	t_philo;


typedef struct s_all
{
	struct timeval cp;
	t_philo *_first;
	t_philo	*head;
	int		philo_cp;
	int		death_timer;
	int		eating_timer;
	int		sleep_timer;
	int		meals_cp;
}	t_all;

//utils
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

t_philo	*ft_new_node(int _id, int _time)
{
	t_philo	*new;

	new = (t_philo *)malloc(sizeof(t_philo));
	if (!new)
		return (NULL);
	new->_id = _id;
	new->state = 1;
	pthread_mutex_init(&new->fork, NULL);
	new->last_meal = _time;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	t_philo	*tmp;

	if (!new)
		return ;
	if (!lst[0])
	{
		lst[0] = new;
		lst[0]->next = new;
		return ;
	}
	tmp = lst[0];
	while (tmp->next != lst[0])
		tmp = tmp->next;
	tmp->next = new;
	new->next = lst[0];
}

void	free_list(t_philo *lst)
{
	while (lst)
	{
		pthread_mutex_destroy(&lst->fork);
		if (lst)
			free(lst);
		lst = lst->next;
	}
}

//parse arguments
void	ft_parse_args(t_all *all, char **av)
{
	int i;

	all->philo_cp = ft_atoi(av[1]);
	all->death_timer = ft_atoi(av[2]) * 1000;
	all->eating_timer = ft_atoi(av[3]) * 1000;
	all->sleep_timer = ft_atoi(av[4]) * 1000;
	if (!av[5])
		all->meals_cp = -1;
	else
		all->meals_cp = ft_atoi(av[5]);
	i = 0;
	gettimeofday(&all->cp, NULL);
	while (++i <= all->philo_cp)
		ft_lstadd_back(&all->head, ft_new_node(i, all->cp.tv_usec));
	all->_first = all->head;
}

void*	test(t_philo *philo)
{
	printf("philo %d\n", philo->_id);
	sleep(1);
	printf("------ HAHA %d ------!!\n",philo->_id);
	return (0);
}


void	ft_exec(t_all all)
{
	int i = 0;

	while (all.head->next != all._first)
	{
		pthread_create(&all.head->philo, NULL, &test, all.head);
		all.head = all.head->next;
	}
}

int main(int ac, char *av[])
{
	t_all all;

	if (ac < 5 || ac > 6)
	{
		printf("Wrong number of arguments !!\n");
		return (0);
	}
	ft_parse_args(&all, av);
	ft_exec(all);

	// t_philo *tmp = all.head;
	// while (tmp->next)
	// {
	// 	printf("%d | %d | %d \n",tmp->_id, tmp->state, tmp->last_meal);
	// 	tmp = tmp->next;
	// 	usleep(all.eating_timer);
	// }
	//free_list(all.head);
	return (0);
}
