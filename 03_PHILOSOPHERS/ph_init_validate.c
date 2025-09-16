/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_init_validate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:03:12 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/16 12:12:10 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ph_init_data(int argc, char **argv, t_data *data)
{
	int		x;

	if (ph_validate_arguments(argc, argv, data))
		return (-1);
	data->start_time = 0;
	data->is_dead = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	x = 0;
	while (x < data->n_philos)
	{
		pthread_mutex_init(&data->forks[x], NULL);
		x++;
	}
	return (1);
}

int	ph_validate_arguments(int argc, char **argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (-1); // Error! Not enough or too many arguments
	if (!ph_is_digit(argv[1]) || !ph_is_digit(argv[2]) ||
			!ph_is_digit(argv[3]) || !ph_is_digit(argv[4]))
		return (-1); // Error! Invalid arguments
	data->n_philos = ph_atol(argv[1]);
	data->time_die = ph_atol(argv[2]);
	data->time_eat = ph_atol(argv[3]);
	data->time_sleep = ph_atol(argv[4]);
	if (argc == 6)
	{
		if (!ph_is_digit(argv[5]) || ph_atol(argv[5]) == 0)
			return (-1); // Error! Invalid 5th argument
		data->n_meals = ph_atol(argv[5]);
	}
	else
		data->n_meals = -1; // Special value = Infinite meals
	if (data->n_philos <= 0 || data->time_die <= 0 ||
			data->time_eat <= 0 || data->time_sleep <= 0)
		return (-1); // Error! Arguments must be greater than 0
	return (0); // Success!
}

int	ph_is_digit(char *num)
{
	int	x;

	x = 0;
	while (num[x])
	{
		if (num[x] < '0' || num[x] > '9')
			return (-1);
		x++;
	}
	return (1);
}

long	ph_atol(char *str)
{
	long	result;
	int		digit;
	int		x;

	result = 0;
	x = 0;
	while (str[x])
	{
		digit = str[x] - '0';
		if (result > (LONG_MAX - digit) / 10)
			return (-1); // Error! Number bigger than LONG_MAX
		result = result * 10 + (str[x] - '0');
		x++;
	}
	return (result);
}

void	ph_init_philos(t_data *data, t_philo *philos)
{
	int		x;

	x = 0;
	while (x < data->n_philos)
	{
		philos[x].id = x + 1;
		philos[x].meals_eaten = 0;
		philos[x].time_last_meal = data->start_time;
		philos[x].left_fork = &data->forks[x];
		philos[x].right_fork = &data->forks[(x + 1) % data->n_philos];
		philos[x].data = data;
		x++;
	}
}
