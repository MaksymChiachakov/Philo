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
// Наші функції спостереження для отримання актуальної інформації
static int	check_death(t_data *data, int i)
{
	long	time;

	pthread_mutex_lock(&data->meal); // Блокуємо змінну їжі
	time = get_time() - data->philos[i].last_meal; // Отримуємо час з відмінням останнього прийому їжі
	pthread_mutex_unlock(&data->meal); // Розблоковуємо змінну їжі
	if (time > data->time_to_die) // Якщо наш час більший чим час до смерті
	{
		pthread_mutex_lock(&data->death); // Блокуємо змінну смерть
		data->dead = 1; // Надаємо значення
		pthread_mutex_unlock(&data->death); // Розблоковуємо змінну смерть
		pthread_mutex_lock(&data->print); // Блокуємо змінну print
		printf("%ld %d died\n", get_time() - data->start_time,
			data->philos[i].id); // Виводимо статус (завдяки printf)
		pthread_mutex_unlock(&data->print); // Розблоковуємо нашу змінну print
		return (1); // Повертаємо 1
	}
	return (0); // В іншому випадку (якщо наш час не більший часу до смерті) то повертаємо 0
}
// Функція для перевіряння їжі
static int	check_meals(t_data *data)
{
	int	i;
	int	all_ate; // Змінна - Всього з'їджено

	if (data->nb_meals == -1) // Якщо кількість -1 (дефолтна)
		return (0); // То повертаємо 0
	all_ate = 1; // Надаємо значеня 1 
	i = 0; // Для пересування у циклі
	while (i < data->nb_philo) // Стільки стільки ж наших філософів
	{
		pthread_mutex_lock(&data->meal); // Блокуємо значення їжі
		if (data->philos[i].meals_eaten < data->nb_meals) // Якщо кількість з'їджених порцій нашого філософа менше чим кількість порцій яку нам потрібно з'їсти
			all_ate = 0; // То надаємо значення 0 нашій змінній
		pthread_mutex_unlock(&data->meal); // Розблоковуємо змінну
		if (!all_ate) // Якщо наш all_ate = 0
			break ; // То ми виходимо з циклу
		i++; // Рухаємось до наступного філософа
	}
	if (all_ate) // Якщо все таки дорівнює 1 після всієї роботи циклу 
	{
		pthread_mutex_lock(&data->death); // Блокуємо змінну смерть 
		data->dead = 1; // Надаємо нове значення
		pthread_mutex_unlock(&data->death); // Розблоковуємо нашу змінну смерть
		return (1); // Повертаємо 1
	}
	return (0); // Якщо все таки all_ate != 1, то повертаємо 0
}
// Функція моніторингу
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
			if (check_death(data, i)) // Якщо повертаємо 1 при перевірці смерті (актуального філософа)
				return (NULL); // Тоді повертаємо NULL
			i++; // Рухаємось до наступного філософа
		}
		if (check_meals(data)) // Перевіряння їжі, якщо повертаєтсья 1 при роботі функції
			return (NULL); // Повертаємо NULL
		usleep(1000); // Спимо 1 секунду (1000 мілісекунд)
	}
	return (NULL); // Повертаємо NULL 
}
