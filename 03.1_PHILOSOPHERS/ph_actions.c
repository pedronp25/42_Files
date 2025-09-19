/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:41:39 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/19 19:52:52 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_eat(t_philo *philos)
{
	ph_take_fork(philos);
	pthread_mutex_lock(&philos->meal_mutex);
	philos->time_last_meal = ph_elapsedtime(philos);
	ph_print(philos, philos->id, "is eating");
	pthread_mutex_lock(&philos->data->print_mutex);
	printf("DBG_EAT: id=%d time_last_meal=%ld\n", philos->id, philos->time_last_meal); // Debugging
	pthread_mutex_unlock(&philos->data->print_mutex);
	if (!ph_split_usleep(&philos->data->death_mutex, philos->data->time_eat,
				&philos->data->simulation_over))
	{
		pthread_mutex_unlock(&philos->meal_mutex);
		ph_putdown_fork(philos);
		return (0);
	}
	philos->meals_eaten++;
	pthread_mutex_lock(&philos->data->print_mutex);
	printf("DBG_EAT2: id=%d meals=%d\n", philos->id, philos->meals_eaten); // Debugging
	pthread_mutex_unlock(&philos->data->print_mutex);
	ph_putdown_fork(philos);
	pthread_mutex_unlock(&philos->meal_mutex);
	return (1);
}

void	ph_take_fork(t_philo *philos)
{
	if (philos->data->n_philos == 1)
	{
		pthread_mutex_lock(philos->right_fork);
		ph_print(philos, philos->id, "has taken a fork");
	}
	else if (philos->id % 2 == 0)
	{
		usleep(50);
		pthread_mutex_lock(philos->right_fork); // Pick up left fork
		ph_print(philos, philos->id, "has taken the left fork");
		pthread_mutex_lock(philos->left_fork); // Pick up right fork
		ph_print(philos, philos->id, "has taken the right fork");
	}
	else
	{
		pthread_mutex_lock(philos->left_fork);
		ph_print(philos, philos->id, "has taken the right fork");
		pthread_mutex_lock(philos->right_fork);
		ph_print(philos, philos->id, "has taken the left fork");
	}
}

void	ph_putdown_fork(t_philo *philos)
{
	if (philos->data->n_philos == 1)
	{
		pthread_mutex_unlock(philos->right_fork);
		ph_print(philos, philos->id, "has put down a fork");
	}
	else if (philos->id % 2 == 0)
	{
		pthread_mutex_unlock(philos->left_fork); // Put down right fork
		ph_print(philos, philos->id, "has put down the right fork");
		pthread_mutex_unlock(philos->right_fork); // Put down left fork
		ph_print(philos, philos->id, "has put down the left fork");
	}
	else
	{
		pthread_mutex_unlock(philos->right_fork);
		ph_print(philos, philos->id, "has put down the left fork");
		pthread_mutex_unlock(philos->left_fork);
		ph_print(philos, philos->id, "has put down the right fork");
	}
}

int	ph_sleep_and_think(t_philo *philos)
{
	ph_print(philos, philos->id, "is sleeping");
	if (!ph_split_usleep(&philos->data->death_mutex, philos->data->time_sleep,
				&philos->data->simulation_over))
			return (0);
	if (philos->data->simulation_over)
		return (0);
	ph_print(philos, philos->id, "is thinking");
	usleep(50);
	return (1);
}

int	ph_split_usleep(pthread_mutex_t *death_mutex, long time_left, int *simulation_over)
{
	int	time_chunk;

	time_left *= 1000; // Convert to microseconds
	time_chunk = time_left / 10; // Could make it larger if needed
	if (time_chunk < 1000)
		time_chunk = 1000;
	if (time_left < time_chunk)
		usleep(time_left);
	while (time_left > 0)
	{
		usleep(time_chunk);
		pthread_mutex_lock(death_mutex);
		if (*simulation_over)
		{
			pthread_mutex_unlock(death_mutex);
			return (0);
		}
		pthread_mutex_unlock(death_mutex);
		time_left -= time_chunk;
	}
	return (1);
}
