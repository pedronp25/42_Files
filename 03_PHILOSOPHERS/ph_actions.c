/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:41:39 by pedromig          #+#    #+#             */
/*   Updated: 2025/10/11 22:49:06 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_eat(t_philo *philos)
{
	if (!ph_take_fork(philos))
		return (0);
	ph_set_time_last_meal(philos, ph_elapsedtime(philos));
	ph_print(philos, philos->id, "is eating");
	ph_usleep(philos->data->time_eat);
	ph_inc_meals_eaten(philos);
	ph_putdown_fork(philos);
	return (1);
}

/*int	ph_take_fork(t_philo *philos)
{
	pthread_mutex_lock(philos->left_fork);
	ph_print(philos, philos->id, "has taken a fork");
	if (philos->data->n_philos == 1)
	{
		usleep(philos->data->time_die * 1000);
		pthread_mutex_unlock(philos->left_fork);
		ph_set_sim_over(philos->data);
		return (0);
	}
	pthread_mutex_lock(philos->right_fork);
	ph_print(philos, philos->id, "has taken a fork");
	return (1);
}*/

int	ph_take_fork(t_philo *philos)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philos->left_fork < philos->right_fork)
	{
		first_fork = philos->left_fork;
		second_fork = philos->right_fork;
	}
	else
	{
		first_fork = philos->right_fork;
		second_fork = philos->left_fork;
	}
	pthread_mutex_lock(first_fork);
	ph_print(philos, philos->id, "has taken a fork");
	if (philos->data->n_philos == 1)
	{
		usleep(philos->data->time_die * 1000);
		pthread_mutex_unlock(first_fork);
		ph_set_sim_over(philos->data);
		return (0);
	}
	pthread_mutex_lock(second_fork);
	ph_print(philos, philos->id, "has taken a fork");
	return (1);
}

void	ph_putdown_fork(t_philo *philos)
{
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
}

int	ph_sleep_and_think(t_philo *philos)
{
	long	time_sleep;

	time_sleep = philos->data->time_sleep;
	ph_print(philos, philos->id, "is sleeping");
	ph_usleep(time_sleep);
	ph_print(philos, philos->id, "is thinking");
	return (1);
}
