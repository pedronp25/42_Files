/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_gettime.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:37:22 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/15 21:38:20 by pedromig         ###   ########.fr       */
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
