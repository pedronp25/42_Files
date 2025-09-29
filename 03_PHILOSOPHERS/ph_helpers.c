/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:52:30 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/29 19:09:07 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	ph_gettime_ms(void)
{
	struct timeval	time;
	long	time_in_ms;

	gettimeofday(&time, NULL);
	time_in_ms = time.tv_sec * 1000L + time.tv_usec / 1000L;
	return (time_in_ms);
}

long	ph_elapsedtime(t_philo *philos)
{
	long	elapsed_time;

	elapsed_time = ph_gettime_ms() - philos->data->start_time;
	return (elapsed_time);
}

void	ph_print(t_philo *philos, int id, char *msg)
{
	pthread_mutex_lock(&philos->data->print_mutex); // To print uninterrupted
	if (!philos->data->simulation_over)
		printf("%ld %i %s\n", ph_elapsedtime(philos), id, msg);
	pthread_mutex_unlock(&philos->data->print_mutex);
}

int	ph_get_sim_over(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->death_mutex);
	ret = data->simulation_over;
	pthread_mutex_unlock(&data->death_mutex);
	return (ret);
}

void	ph_set_sim_over(t_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->simulation_over = 1;
	pthread_mutex_unlock(&data->death_mutex);
}

long	ph_get_time_last_meal(t_philo *philos)
{
	long time;

	pthread_mutex_lock(&philos->meal_mutex);
	time = philos->time_last_meal;
	pthread_mutex_unlock(&philos->meal_mutex);
	return time;
}

/*
int	ph_get_is_eating(t_philo *philos)
{
	int	ret;

	pthread_mutex_lock(&philos->meal_mutex);
	ret = philos->is_eating;
	pthread_mutex_unlock(&philos->meal_mutex);
	return (ret);
}
*/

void	ph_set_time_last_meal(t_philo *philos, long new_time)
{
	pthread_mutex_lock(&philos->meal_mutex);
	//philos->is_eating = 1;
	philos->time_last_meal = new_time;
	pthread_mutex_unlock(&philos->meal_mutex);
}

int	ph_get_meals_eaten(t_philo *philos)
{
	int meals;

	pthread_mutex_lock(&philos->meal_mutex);
	meals = philos->meals_eaten;
	pthread_mutex_unlock(&philos->meal_mutex);
	return meals;
}

void	ph_inc_meals_eaten(t_philo *philos)
{
	pthread_mutex_lock(&philos->meal_mutex);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->meal_mutex);
}

void	ph_set_meals_eaten(t_philo *philos, int value)
{
    pthread_mutex_lock(&philos->meal_mutex);
    philos->meals_eaten = value;
    pthread_mutex_unlock(&philos->meal_mutex);
}
