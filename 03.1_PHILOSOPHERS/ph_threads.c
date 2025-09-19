/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:06:26 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/19 01:50:21 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ph_create_threads(t_philo *philos)
{
	int	x;

	x = 0;
	while (x < philos->data->n_philos)
	{
		pthread_create(&philos[x].thread, NULL, ph_routine, &philos[x]);
		x++;
	}
	pthread_create(&philos->data->monitor, NULL, ph_monitor, philos);
}

void	ph_join_threads(t_philo *philos)
{
	int	x;

	x = 0;
	while (x < philos->data->n_philos)
	{
		pthread_join(philos[x].thread, NULL);
		x++;
	}
	pthread_join(philos->data->monitor, NULL);
}

void	*ph_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (!philos->data->simulation_over)
	{
		if (!ph_eat(philos))
			break ;
		if (philos->data->simulation_over)
			break ;
		if (!ph_sleep_and_think(philos))
			break ;
		if (philos->data->simulation_over)
			break ;
	}
	return (NULL);
}

void	*ph_monitor(void *arg)
{
	t_philo	*philos;
	int		n_philos_full;

	philos = (t_philo *)arg;
	while (!philos->data->simulation_over)
	{
		ph_check_meals(philos, &n_philos_full);
		if (philos->data->n_meals != -1 && n_philos_full == philos->data->n_philos)
		{
			philos->data->simulation_over = 1;
			pthread_mutex_lock(&philos->data->print_mutex);
			printf("%ld All philosophers ate enough\n", ph_elapsedtime(philos));
			pthread_mutex_unlock(&philos->data->print_mutex);
			break ;
		}
		usleep(100); // Small usleep to not overload CPU
	}
	return (NULL);
}

void	ph_check_meals(t_philo *philos, int	*n_philos_full)
{
	int		x;
	long	time_since_meal;

	*n_philos_full = 0;
	x = 0;
	while (x < philos->data->n_philos)
	{
		pthread_mutex_lock(&philos[x].meal_mutex);
		time_since_meal = ph_elapsedtime(philos) - philos[x].time_last_meal;
		if (time_since_meal >= philos->data->time_die)
		{
			pthread_mutex_lock(&philos->data->death_mutex);
			philos->data->simulation_over = 1;
			pthread_mutex_unlock(&philos->data->death_mutex);
			pthread_mutex_lock(&philos->data->print_mutex);
			printf("%ld %i has died (last meal at %ld)\n",
					ph_elapsedtime(philos), philos[x].id, philos[x].time_last_meal); // Debugging
			pthread_mutex_unlock(&philos->data->print_mutex);
			pthread_mutex_unlock(&philos[x].meal_mutex);
			return ;
		}
		if (philos->data->n_meals != -1 && philos[x].meals_eaten >= philos->data->n_meals)
			(*n_philos_full)++;
		pthread_mutex_unlock(&philos[x].meal_mutex);
		x++;
	}
}
