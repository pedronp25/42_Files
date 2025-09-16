/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:41:39 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/17 00:22:37 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ph_eat(t_philo *philos)
{
	ph_take_fork(philos);
	ph_print(philos, philos->id, "is eating");
	philos->time_last_meal = ph_elapsedtime(philos);
	if (!ph_split_usleep(&philos->data->death_mutex, philos->data->time_eat))
		return (-1);
	philos->meals_eaten++;
	ph_putdown_fork(philos);
	return (1);
}

void	ph_take_fork(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->left_fork); // Pick up left fork
		ph_print(philos, philos->id, "has taken the left fork");
		pthread_mutex_lock(philos->right_fork); // Pick up right fork
		ph_print(philos, philos->id, "has taken the right fork");
	}
	else
	{
		pthread_mutex_lock(philos->right_fork);
		ph_print(philos, philos->id, "has taken the right fork");
		pthread_mutex_lock(philos->left_fork);
		ph_print(philos, philos->id, "has taken the left fork");
	}
}

void	ph_putdown_fork(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_unlock(philos->right_fork); // Put down right fork
		ph_print(philos, philos->id, "has put down the right fork");
		pthread_mutex_unlock(philos->left_fork); // Put down left fork
		ph_print(philos, philos->id, "has put down the left fork");
	}
	else
	{
		pthread_mutex_unlock(philos->left_fork);
		ph_print(philos, philos->id, "has put down the left fork");
		pthread_mutex_unlock(philos->right_fork);
		ph_print(philos, philos->id, "has put down the right fork");
	}
}

int	ph_sleep_and_think(t_philo *philos)
{
	ph_print(philos, philos->id, "is sleeping");
	if (!ph_split_usleep(&philos->data->death_mutex, philos->data->time_sleep))
			return (-1);
	if (simulation_over)
		return (-1);
	ph_print(philos, philos->id, "is thinking");
	usleep(50); // Optional delay to prevent a philosopher to get stuck waiting for a fork
	return (1);
}

int	ph_split_usleep(pthread_mutex_t *death_mutex, long time_left)
{
	int	time_chunk;

	time_left *= 1000; // Convert to microseconds
	time_chunk = 1000; // Could make it larger if needed
	while (time_left > 0)
	{
		usleep(time_chunk);
		pthread_mutex_lock(death_mutex);
		if (simulation_over)
		{
			pthread_mutex_unlock(death_mutex);
			return (-1);
		}
		pthread_mutex_unlock(death_mutex);
		time_left -= time_chunk;
	}
	return (1);
}
