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
# include <pthread.h> // Наша бібліотека потоків 
# include <sys/time.h> // Бібліотека для роботи з часом

typedef struct s_data	t_data; // Прототип для використання у структурі s_philo

// Створення структури нашого філософа
typedef struct s_philo
{
	int				id; // Його ідентифікатор
	int				meals_eaten; // Кількість з'їджених порцій
	long			last_meal; // Останній прийом їжі
	pthread_t		thread; // Потік (нитка)
	pthread_mutex_t	*left_fork; // Ліва виделка
	pthread_mutex_t	*right_fork; // Права виделка
	t_data			*data; // Та наша Data
}	t_philo;

// Створення нашої data
typedef struct s_data
{
	int				nb_philo; // Кількість філософів
	int				time_to_die; // Час до смерті
	int				time_to_eat; // Час до прийому їжі
	int				time_to_sleep; // Час для сну
	int				nb_meals; // Кількість порцій (якщо є у 5-му аргументі (av[5]))
	int				dead; // Змінна смерті
	long			start_time; // Початковий час
	pthread_mutex_t	*forks; // Список (масив) виделок
	pthread_mutex_t	print; // Поток print
	pthread_mutex_t	death; // Поток death
	pthread_mutex_t	meal; // Поток meal
	t_philo			*philos; // Та наші філософи
}	t_data;

// Всі наші функції
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
