/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:41:39 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/15 21:42:10 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_eat(t_philo *philos)
{
	ph_take_fork(philos);
	printf("%ld %i is eating", ph_elapsedtime(), philos->id);
	usleep(philos->data->time_eat * 1000);
	ph_putdown_fork(philos);
}

void	ph_take_fork(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->left_fork); // Pick up left fork
		printf("%ld %i has taken the left fork", ph_elapsedtime(), philos->id);
		pthread_mutex_lock(philos->right_fork); // Pick up right fork
		printf("%ld %i has taken the right fork", ph_elapsedtime(), philos->id);
	}
	else
	{
		pthread_mutex_lock(philos->right_fork); // Pick up right fork
		printf("%ld %i has taken the right fork", ph_elapsedtime(), philos->id);
		pthread_mutex_lock(philos->left_fork); // Pick up left fork
		printf("%ld %i has taken the left fork", ph_elapsedtime(), philos->id);
	}
}

void	ph_putdown_fork(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_unlock(philos->right_fork); // Pick up left fork
		printf("%ld %i has put down the right fork", ph_elapsedtime(), philos->id);
		pthread_mutex_unlock(philos->left_fork); // Pick up right fork
		printf("%ld %i has put down the left fork", ph_elapsedtime(), philos->id);
	}
	else
	{
		pthread_mutex_unlock(philos->left_fork); // Pick up left fork
		printf("%ld %i has put down the left fork", ph_elapsedtime(), philos->id);
		pthread_mutex_unlock(philos->right_fork); // Pick up right fork
		printf("%ld %i has put down the right fork", ph_elapsedtime(), philos->id);
	}
}
