/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhachem <mhachem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 12:01:09 by mhachem           #+#    #+#             */
/*   Updated: 2025/12/07 13:50:30 by mhachem          ###   ########.fr       */
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
