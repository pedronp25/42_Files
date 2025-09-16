/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:39:46 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/16 12:30:35 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data 	data;
	t_philo	philos[200];

	if (!ph_init_data(argc, argv, &data))
		return (1); // Couldn't initiate data; Cleanup left;
	ph_init_philos(&data, philos);
	data.start_time = ph_gettime_ms();
}

void	ph_create_thread(t_philo *philos)
{
	int	x;

	x = 0;
	while (x < philos->data->n_philos)
	{
		pthread_create(&philos[x].thread, NULL, ph_routine, &philos[x]);
		x++;
	}
}

void	*ph_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (!simulation_over(philos->data))
	{
		ph_eat(philos);
		usleep(philos->data->time_sleep * 1000);
	}
}


