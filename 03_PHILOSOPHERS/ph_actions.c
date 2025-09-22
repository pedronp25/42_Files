/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:41:39 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/22 04:38:30 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <pthread.h>

int	ph_eat(t_philo *philos)
{
	ph_take_fork(philos);
	if (ph_get_sim_over(philos->data))
		return (0);
	pthread_mutex_lock(&philos->meal_mutex);
	philos->time_last_meal = ph_elapsedtime(philos);
	ph_print(philos, philos->id, "is eating");
	usleep(philos->data->time_eat * 1000);
	philos->meals_eaten++;
	ph_putdown_fork(philos);
	pthread_mutex_unlock(&philos->meal_mutex);
	return (1);
}

void	ph_take_fork(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		usleep(50);
		pthread_mutex_lock(philos->right_fork); // Pick up left fork
		ph_print(philos, philos->id, "has taken the left fork");
		pthread_mutex_lock(philos->left_fork); // Pick up right fork
		ph_print(philos, philos->id, "has taken the right fork");
	}
	else if (philos->id % 2 == 1)
	{
		pthread_mutex_lock(philos->left_fork);
		ph_print(philos, philos->id, "has taken the right fork");
		pthread_mutex_lock(philos->right_fork);
		ph_print(philos, philos->id, "has taken the left fork");
	}
	else if (philos->data->n_philos == 1)
	{
		pthread_mutex_lock(philos->right_fork);
		ph_print(philos, philos->id, "has taken a fork");
		usleep(philos->data->time_die * 1000);
		ph_set_sim_over(philos->data);
	}
}

void	ph_putdown_fork(t_philo *philos)
{
	if (philos->id % 2 == 0)
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
	usleep(philos->data->time_sleep * 1000);
	if (ph_get_sim_over(philos->data))
		return (0);
	ph_print(philos, philos->id, "is thinking");
	usleep(50);
	return (1);
}

int	ph_is_dead(t_philo *philos)
{
	long	current_time;
	long	time_since_meal;
	
	current_time = ph_elapsedtime(philos);

	pthread_mutex_lock(&philos->meal_mutex);
	time_since_meal = current_time - philos->time_last_meal;
	pthread_mutex_unlock(&philos->meal_mutex);
	return (time_since_meal >= philos->data->time_die);
}
