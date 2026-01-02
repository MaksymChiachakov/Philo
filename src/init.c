/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:49:52 by mhachem           #+#    #+#             */
/*   Updated: 2025/12/07 13:35:16 by mhachem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// Ініціалізація дати
int	init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atoi(av[1]); // Кількість філософів (1-ий аргумент)
	data->time_to_die = ft_atoi(av[2]); // Час до смерті (2-ий аргумент)
	data->time_to_eat = ft_atoi(av[3]); // Час до їжі (3-ій аргумент)
	data->time_to_sleep = ft_atoi(av[4]); // Час для сну (4-ий аргумент)
	if (ac == 6) // Якщо аргументів 6
		data->nb_meals = ft_atoi(av[5]); // То для змінної Кількість порцій, 5-ий аргумент
	else
		data->nb_meals = -1; // В іншому випадку дефолтне значення (-1)
	if (data->nb_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (ac == 6 && data->nb_meals <= 0)) // Перевірка для запобігання можливих помилок (парсинг аргументів)
	{
		printf("Error: invalid arguments\n"); // Афішування проблеми
		return (1); // Повертаємо 1
	}
	// Надаємо дефолтні значення
	data->dead = 0; // 0 смертей
	data->start_time = 0; // Початковий час - 0
	data->philos = NULL; // Філософи - NULL
	data->forks = NULL; // Виделки - NULL
	pthread_mutex_init(&data->print, NULL); // Ініціалізація print
	pthread_mutex_init(&data->death, NULL); // Ініціалізація death
	pthread_mutex_init(&data->meal, NULL); // Ініціалізація meal
	return (0); // Повертаємо 0
}
// Ініціалізація виделок
int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo); // Створення пам'яті (розмір в байтах нашого потоку множимо на кілкьість наших філософів)
	if (!data->forks) // Якщо виделок немає (0)
		return (1); // Повертаємо 1
	i = 0;
	while (i < data->nb_philo) // Стільки стільки ж наших філософів
	{
		if (pthread_mutex_init(&data->forks[i], NULL)) // Ініціалізація виделок (потоків)
			return (1); // Повертаємо 1
		i++; // Рухаємось до наступного філософа
	}
	return (0); // Повертаємо 0
}
// Ініціалізація філософів
int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->nb_philo); // Створення пам'яті (множення розміру нашого філософа на кількість філософів)
	if (!data->philos) // Перевіка (la protection malloc)
		return (1);
	i = 0;
	while (i < data->nb_philo) // Стільки стільки ж наших філософів
	{
		data->philos[i].id = i + 1; // Надавання нашому філософу - id
		data->philos[i].meals_eaten = 0; // Кількість з'їджених порцій - 0
		data->philos[i].last_meal = 0; // Останній прийом їжі - 0
		data->philos[i].data = data; // Присвоєння дати
		data->philos[i].left_fork = &data->forks[i]; // Надавання лівої виделки
		data->philos[i].right_fork = &data->forks[(i + 1) % data->nb_philo]; // Надавання правої виделки
		i++; // Рухаємось до наступного філософа
	}
	return (0); // Повертаємо 0
}
// Чистка пам'яті
void	free_all(t_data *data)
{
	int	i;

	if (data->forks) // Якщо є наші виделки
	{
		i = 0;
		while (i < data->nb_philo) // Стільки стільки ж наших філософів
		{
			pthread_mutex_destroy(&data->forks[i]); // Видаляємо виделку (потік)
			i++; // Рухаємо до наступної виделку (або наступного потоку)
		}
		free(data->forks); // Чистимо весь список виделок (потоків)
	}
	if (data->philos) // Якщо є список філософів
		free(data->philos); // Очищаємо його
	pthread_mutex_destroy(&data->print); // Очищаємо наш поток print
	pthread_mutex_destroy(&data->death); // Очищаємо наш поток print
	pthread_mutex_destroy(&data->meal); // Очищаємо наш поток print
}
