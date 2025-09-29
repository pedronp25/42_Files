/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:41:39 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/29 19:23:03 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_eat(t_philo *philos)
{
//	if (ph_get_meals_eaten(philos) < n_rounds /*not set yet*/)
//		ph_wait(); // Only and idea of what could be a function
	ph_take_fork(philos);
	ph_set_time_last_meal(philos, ph_elapsedtime(philos));
	ph_print(philos, philos->id, "is eating");
	usleep(philos->data->time_eat * 1000);
	ph_inc_meals_eaten(philos);
	ph_putdown_fork(philos);
	return (1);
}

void	ph_take_fork(t_philo *philos)
{
	if (philos->data->n_philos == 1)
	{
		pthread_mutex_lock(philos->left_fork);
		ph_print(philos, philos->id, "has taken a fork");
		usleep(philos->data->time_die * 1000);
		pthread_mutex_unlock(philos->left_fork);
		ph_set_sim_over(philos->data);
	}
	else if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->right_fork);
		ph_print(philos, philos->id, "has taken the right fork");
		pthread_mutex_lock(philos->left_fork);
		ph_print(philos, philos->id, "has taken the left fork");
	}
	else
	{
		pthread_mutex_lock(philos->left_fork);
		ph_print(philos, philos->id, "has taken the left fork");
		pthread_mutex_lock(philos->right_fork);
		ph_print(philos, philos->id, "has taken the right fork");
	}
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
	ph_print(philos, philos->id, "is sleeping");
	usleep(philos->data->time_sleep * 1000);
	//if (ph_get_sim_over(philos->data))
	//	return (0);
	ph_print(philos, philos->id, "is thinking");
	return (1);
}

int	ph_is_dead(t_philo *philos)
{
	long	time_since_meal;

	pthread_mutex_lock(&philos->meal_mutex);
	time_since_meal = ph_elapsedtime(philos) - philos->time_last_meal;
	pthread_mutex_unlock(&philos->meal_mutex);
	if (philos->is_eating == 0 && time_since_meal >= philos->data->time_die)
		return (1);
	return (0);
}
