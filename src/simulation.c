/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:47:48 by mhachem           #+#    #+#             */
/*   Updated: 2025/12/07 13:35:30 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Старт симуляції
int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor_thread;

	data->start_time = get_time(); // Получаємо наш час (актуальний)
	i = 0;
	while (i < data->nb_philo) // Стільки стільки ж наших філософів
	{
		data->philos[i].last_meal = data->start_time; // Ставимо значення останнього прийому їжі для кожного філософа
		if (pthread_create(&data->philos[i].thread, NULL,
				routine, &data->philos[i])) // Якщо повертаєтсья 1 при роботі цієї функції
			return (1); // То ми повертаємо 1
		i++; // Рухаємось до наступного філософа
	}
	if (pthread_create(&monitor_thread, NULL, monitor, data)) // Якщо і тут получаємо 1 при роботі функції
		return (1); // То ми повертаємо 1
	i = 0;
	while (i < data->nb_philo) // Стільки стільки ж наших філософів
	{
		pthread_join(data->philos[i].thread, NULL); // Запускаємо нашу функцію з нашим актуальним філософом
		i++; // Рухаємось до наступного філософа
	}
	pthread_join(monitor_thread, NULL); // У кінці у любому випадку виконуємо цю функцію
	return (0); // Повертаємо 0
}
