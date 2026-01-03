/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchiacha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 12:10:44 by mchiacha          #+#    #+#             */
/*   Updated: 2026/01/03 12:10:46 by mchiacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (printf("Error: wrong number of arguments\n"), 1);
	if (init_data(&data, ac, av))
		return (1);
	if (init_forks(&data))
		return (free_all(&data), 1);
	if (init_philos(&data))
		return (free_all(&data), 1);
	if (start_simulation(&data))
		return (free_all(&data), 1);
	free_all(&data);
	return (0);
}
