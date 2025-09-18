/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:52:30 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/17 23:06:13 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ph_gettime_ms(void)
{
	struct timeval	time;
	long	time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = time.tv_sec * 1000L + time.tv_usec / 1000L;
	return (time_in_ms);
}

long	ph_elapsedtime(t_philo *philos)
{
	long	elapsed_time;

	elapsed_time = ph_gettime_ms() - philos->data->start_time;
	return (elapsed_time);
}

void	ph_print(t_philo *philos, int id, char *msg)
{
	pthread_mutex_lock(&philos->data->print_mutex); // To print uninterrupted
	if (!philos->data->simulation_over)
		printf("%ld %i %s\n", ph_elapsedtime(philos), id, msg);
	pthread_mutex_unlock(&philos->data->print_mutex);
}
