/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:48:22 by mhachem           #+#    #+#             */
/*   Updated: 2025/12/07 13:35:17 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, int i)
{
	long	time;

	pthread_mutex_lock(&data->meal);
	time = get_time() - data->philos[i].last_meal;
	pthread_mutex_unlock(&data->meal);
	if (time > data->time_to_die)
	{
		pthread_mutex_lock(&data->death);
		data->dead = 1;
		pthread_mutex_unlock(&data->death);
		pthread_mutex_lock(&data->print);
		printf("%ld %d died\n", get_time() - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print);
		return (1);
	}
	return (0);
}

static int	check_meals(t_data *data)
{
	int	i;
	int	all_ate;

	if (data->nb_meals == -1)
		return (0);
	all_ate = 1;
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->meal);
		if (data->philos[i].meals_eaten < data->nb_meals)
			all_ate = 0;
		pthread_mutex_unlock(&data->meal);
		if (!all_ate)
			break ;
		i++;
	}
	if (all_ate)
	{
		pthread_mutex_lock(&data->death);
		data->dead = 1;
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nb_philo)
		{
			if (check_death(data, i))
				return (NULL);
			i++;
		}
		if (check_meals(data))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
