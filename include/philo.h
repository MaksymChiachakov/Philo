/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:12:24 by mhachem           #+#    #+#             */
/*   Updated: 2025/12/07 12:46:22 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				dead;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
	pthread_mutex_t	meal;
	t_philo			*philos;
}	t_data;

int		ft_atoi(const char *str);
int		init_data(t_data *data, int ac, char **av);
int		init_philos(t_data *data);
int		init_forks(t_data *data);
void	free_all(t_data *data);
long	get_time(void);
void	print_status(t_philo *philo, char *status);
int		is_dead(t_data *data);
void	ft_usleep(long time);
void	*routine(void *arg);
void	*monitor(void *arg);
int		start_simulation(t_data *data);

#endif
