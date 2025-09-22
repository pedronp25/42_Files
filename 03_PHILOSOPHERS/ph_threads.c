/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:06:26 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/22 22:31:56 by pedromig         ###   ########.fr       */
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
	while (!ph_get_sim_over(philos->data))
	{
		if (!ph_eat(philos) || ph_get_sim_over(philos->data))
			return (NULL);
		if (!ph_sleep_and_think(philos) || ph_get_sim_over(philos->data))
			return (NULL);
	}
	return (NULL);
}

void	*ph_monitor(void *arg)
{
	t_philo	*philos;
	int		n_philos_full;

	philos = (t_philo *)arg;
	usleep(1000); // wait 1ms to ensure all threads start and update time_last_meal
	while (!ph_get_sim_over(philos->data))
	{
		ph_check_meals(philos, &n_philos_full);
		if (philos->data->n_meals != -1 && n_philos_full == philos->data->n_philos)
		{
			ph_set_sim_over(philos->data);
			pthread_mutex_lock(&philos->data->print_mutex);
			printf("%ld All philosophers ate enough\n", ph_elapsedtime(philos));
			pthread_mutex_unlock(&philos->data->print_mutex);
			return (NULL); ;
		}
		usleep(500); // Small usleep to not overload CPU
	}
	return (NULL);
}

void	ph_check_meals(t_philo *philos, int	*n_philos_full)
{
	int		x;

	*n_philos_full = 0;
	x = 0;
	while (x < philos->data->n_philos)
	{
		// Add debug output:
    	pthread_mutex_lock(&philos[x].meal_mutex);
    	long current_time = ph_elapsedtime(philos);
    	long time_since_meal = current_time - philos[x].time_last_meal;
   		int is_eating = philos[x].is_eating;  // if you added this flag
    
    	printf("DBG_DEATH_CHECK: id=%d current=%ld last_meal=%ld gap=%ld is_eating=%d\n", 
           philos[x].id, current_time, philos[x].time_last_meal, time_since_meal, is_eating);

    	pthread_mutex_unlock(&philos[x].meal_mutex);
		if (ph_is_dead(&philos[x]))
		{
			ph_set_sim_over(philos->data);
			pthread_mutex_lock(&philos->data->print_mutex);
			printf("%ld %i has died (last meal at %ld)\n",
					ph_elapsedtime(philos), philos[x].id, ph_get_time_last_meal(&philos[x])); // Debugging
			pthread_mutex_unlock(&philos->data->print_mutex);
			return ;
		}
		if (philos->data->n_meals != -1 &&
				ph_get_meals_eaten(&philos[x]) >= philos->data->n_meals)
			(*n_philos_full)++;
		x++;
	}
}
