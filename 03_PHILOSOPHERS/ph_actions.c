/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:41:39 by pedromig          #+#    #+#             */
/*   Updated: 2025/10/11 01:38:22 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_eat(t_philo *philos)
{
	if (!ph_take_fork(philos))
		return (0);
	ph_set_time_last_meal(philos, ph_elapsedtime(philos));
	ph_print(philos, philos->id, "is eating");
	//usleep(philos->data->time_eat * 1000);
	ph_usleep(philos->data->time_eat);
	ph_inc_meals_eaten(philos);
	ph_putdown_fork(philos);
	return (1);
}

int	ph_take_fork(t_philo *philos)
{
	if (philos->data->n_philos == 1)
	{
		pthread_mutex_lock(philos->left_fork);
		ph_print(philos, philos->id, "has taken a fork");
		usleep(philos->data->time_die * 1000);
		pthread_mutex_unlock(philos->left_fork);
		ph_set_sim_over(philos->data);
		return (0);
	}
	else if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->right_fork);
		ph_print(philos, philos->id, "has taken a fork");
		pthread_mutex_lock(philos->left_fork);
		ph_print(philos, philos->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philos->left_fork);
		ph_print(philos, philos->id, "has taken a fork");
		pthread_mutex_lock(philos->right_fork);
		ph_print(philos, philos->id, "has taken a fork");
	}
	return (1);
}

void	ph_putdown_fork(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_unlock(philos->right_fork);
		//ph_print(philos, philos->id, "has put down the left fork");
		pthread_mutex_unlock(philos->left_fork);
		//ph_print(philos, philos->id, "has put down the right fork");
	}
	else
	{
		pthread_mutex_unlock(philos->left_fork);
		//ph_print(philos, philos->id, "has put down the right fork");
		pthread_mutex_unlock(philos->right_fork);
		//ph_print(philos, philos->id, "has put down the left fork");
	}
}

int	ph_sleep_and_think(t_philo *philos)
{
	long	time_eat;
	long	time_sleep;

	time_eat = philos->data->time_eat;
	time_sleep = philos->data->time_sleep;
	ph_print(philos, philos->id, "is sleeping");
	//usleep(philos->data->time_sleep * 1000);
	ph_usleep(philos->data->time_sleep);
	ph_print(philos, philos->id, "is thinking");
	//if (philos->data->n_philos % 2 != 0 && time_eat > time_sleep)
	//	usleep((time_eat - time_sleep) * 1000); // Artificial time_think to keep philos from racing in front of others
	return (1);
}
