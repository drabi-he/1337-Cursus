/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 14:43:03 by hdrabi            #+#    #+#             */
/*   Updated: 2022/01/14 16:11:30 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

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
	int				meal_cp;
	int				philo_dead;
	size_t			ground0;
	int				all_full;
	pthread_mutex_t	writing;
}	t_all;

//utils
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_putstr(char *str, int error);
size_t	ft_timestamp(void);
size_t	ft_time_diff(size_t current, size_t past);
void	ft_print(t_all *all, int _id, char *str);
void	ft_sleep(t_all *all, size_t time);
int		ft_atoi(const char *str);
t_philo	*ft_new_node(int _id, t_all *all);
void	ft_lstadd_back(t_philo **lst, t_philo *new);

//parsing
void	ft_free_list(t_all *all);
int		ft_check_digits(char **av);
int		ft_parse_args(t_all *all, char **av);

//exec
void	ft_eats(t_all *all, t_philo *philo);
void	*launch(void *philo);
void	ft_dead(t_all *all, t_philo *philo);
int		ft_exec(t_all *all);

#endif
