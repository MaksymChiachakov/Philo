/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:49:41 by mhachem           #+#    #+#             */
/*   Updated: 2025/12/07 13:35:17 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// Харчування нашого філософа
static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork); // Блокування змінної
	print_status(philo, "has taken a fork"); // Афішування статусу (філософ взяв виделку)
	if (philo->data->nb_philo == 1) // Якщо це 1-ий філософ
	{
		pthread_mutex_unlock(philo->left_fork); // Блокуємо значення лівої виделки (від філософа)
		ft_usleep(philo->data->time_to_die); // І наш філософ лягає спати
		return ; // Вихід з функції
	}
	// Якщо це був не філософ з номером 1
	pthread_mutex_lock(philo->right_fork); // То блокуємо значення правої виделки від нашого філософа
	print_status(philo, "has taken a fork"); // Афішуємо статус (взяв виделку)
	print_status(philo, "is eating"); // Афішуємо що наш філософ їсть
	pthread_mutex_lock(&philo->data->meal); // Блокуємо змінну (їжа)
	philo->last_meal = get_time(); // Надаємо час коли був останній прийом їжі (щойно)
	philo->meals_eaten++; // Добавляємо скільки порцій з'їв наш філософ (всі філософи повинні поїсти 7 разів)
	pthread_mutex_unlock(&philo->data->meal); // Розблоковуємо змінну 
	ft_usleep(philo->data->time_to_eat); // Наш філософ лягає спати (на той час який ми дали в аргументах при запуску програми)
	pthread_mutex_unlock(philo->right_fork); // Розблокування правої виделки
	pthread_mutex_unlock(philo->left_fork); // Розблокування лівої виделки
}
// Функція для сну нашого філософа
static void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping"); // Виводимо статус 
	ft_usleep(philo->data->time_to_sleep); // Укладаємо спати нашого філософа на той час, який ми отримали в аргументах при запуску програми
}
// Функція для роздомувів нашого філософа
static void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking"); // Просте афішування статусу, нічого більше не потрібно
}
// І наша рутина (яка повинна повторюватись)
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg; // Получаємо наших філософів 
	if (philo->id % 2 == 0) // Якщо його номер (id) парний, то..
		ft_usleep(1); // Він спить
	while (!is_dead(philo->data)) // До тих пір поки філософ живий
	{
		philo_eat(philo); // Філософ їсть
		if (philo->data->nb_meals != -1
			&& philo->meals_eaten >= philo->data->nb_meals)
			break ; // Якщо наш філософ уже достатньо поїв (стільки ж стільки ми йому вказали в аргументах при запуску програми) то ми виходимо з циклу
		philo_sleep(philo); // Філософ спить
		philo_think(philo); // Філософ думає
	}
	return (NULL); // Повертаємо NULL 
}
