/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:50:09 by mhachem           #+#    #+#             */
/*   Updated: 2025/12/07 13:35:15 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// Наш ft_atoi для роботи з аргументами нашої програми на самому старті
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
// Функція для отримання актуального часу
long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
// Функція для очікування (сну)
void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(500);
}
// Функція для афішування статусу
void	print_status(t_philo *philo, char *status)
{
	long	timestamp;
	// Блокування змінних для подальшої коректної роботи з ними
	pthread_mutex_lock(&philo->data->print); 
	pthread_mutex_lock(&philo->data->death);
	if (!philo->data->dead) // Якщо наш філософ живий
	{
		timestamp = get_time() - philo->data->start_time; // Отримуємо актуальний час
		printf("%ld %d %s\n", timestamp, philo->id, status); // Саме афішування
	}
	// Після завершення роботи з нашими змінними, ми розблоковуємо наші змінні для інших функцій
	pthread_mutex_unlock(&philo->data->death);
	pthread_mutex_unlock(&philo->data->print);
}
// Функція для перевірки чи наш філософ мертвий
int	is_dead(t_data *data)
{
	int	dead; // Створення змінної (смерть)

	pthread_mutex_lock(&data->death); // Те саме блокування змінної
	dead = data->dead; // Занесення у нього значення
	pthread_mutex_unlock(&data->death); // Розблокування змінної
	return (dead); // Повернення значення
}
