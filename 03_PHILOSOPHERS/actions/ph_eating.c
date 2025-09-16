/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_eating.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:41:39 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/16 21:07:34 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	ph_eat(t_philo *philos)
{
	ph_take_fork(philos);
	ph_print(philos, philos->id, "is eating");
	philos->time_last_meal = ph_elapsedtime(philos);
	usleep(philos->data->time_eat * 1000);
	philos->meals_eaten++;
	ph_putdown_fork(philos);
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

void	ph_sleep_and_think(t_philo *philos)
{
	ph_print(philos, philos->id, "is sleeping");
	usleep(philos->data->time_sleep * 1000);
	ph_print(philos, philos->id, "is thinking");
	usleep(50); // Optional delay to prevent a philosopher to get stuck waiting for a fork
}

int	ph_split_and_run(long time)
{
	time /= 2;
	usleep(time * 1000);
	if (simulation_over)
		return (-1);
	usleep(time * 1000);
	return (1);
}
