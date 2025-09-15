/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_initiate_philos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:46:38 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/15 17:47:10 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*ph_init_philos(t_data *data)
{
	t_philo	*philos;
	int		x;

	philos = malloc(sizeof(*philos) * data->n_philos);
	if (!philos)
		return (NULL);
	x = 0;
	while (x < data->n_philos)
	{
		philos[x].id = x + 1;
		philos[x].meals_eaten = 0;
		philos[x].time_last_meal = data->start_time;
		philos[x].left_fork = &data->forks[x];
		philos[x].right_fork = &data->forks[(x + 1) % data->n_philos];
		philos[x].data = data;
		x++;
	}
	return (philos);
}
