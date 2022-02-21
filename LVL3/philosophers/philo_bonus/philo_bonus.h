/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:16:53 by hdrabi            #+#    #+#             */
/*   Updated: 2022/02/21 11:48:35 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <semaphore.h>

typedef struct s_philo
{
	int				_id;
	pid_t			philo;
	size_t			last_meal;
	int				is_full;
	struct s_all	*all;
	struct s_philo	*next;
}	t_philo;

typedef struct s_all
{
	int		philo_cp;
	t_philo	*_first;
	t_philo	*head;
	size_t	death_timer;
	size_t	sleep_timer;
	size_t	eating_timer;
	int		meal_cp;
	int		philo_dead;
	size_t	ground0;
	int		all_full;
	sem_t	*forks;
	sem_t	*writing;
}	t_all;

//utils
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_putstr(char *str, int error);
int		ft_check_digits(char **av);
int		ft_atoi(const char *str);
void	ft_sem_init(t_all *all);
t_philo	*ft_new_node(int _id, t_all *all);
void	ft_lstadd_back(t_philo **lst, t_philo *new);
size_t	ft_timestamp(void);

//parsing
size_t	ft_time_diff(size_t current, size_t past);
void	ft_print(t_all *all, int _id, char *str);
void	ft_sleep(t_all *all, size_t time);
void	ft_free_list(t_all *all);
int		ft_parse_args(t_all *all, char **av);

//exec
void	*ft_death(void *p);
void	ft_eats(t_all *all, t_philo *philo);
void	ft_start(t_philo *philo, t_all *all);
void	ft_exit(t_all *all);
void	ft_exec(t_all *all);

#endif
