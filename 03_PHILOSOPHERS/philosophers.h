/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:59:46 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/15 17:47:48 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	long			n_philos; // Number of philosophers
	long			time_die; // Time to die (milisseconds)
	long			time_eat; // Time to eat (milisseconds)
	long			time_sleep; // Time to sleep (milisseconds)
	long			n_meals; // Number of meals a philosopher must have (Optional)
	
	int				is_dead; // Value to stop simulation when someone dies
	long			start_time; // Start time in milisseconds
	
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;

}	t_data;

typedef struct s_philo
{
	int				id; // This philosopher's ID
	int				meals_eaten; // Number of meals eaten for this philosopher
	long			time_last_meal; // Timestamp of last meal eaten
	
	pthread_t		thread; // This philosopher's thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	t_data			*data;

}	t_philo;


t_data	*ph_init_data(int argc, char **argv);
int		ph_validate_arguments(int argc, char **argv, t_data *data);
int		ph_is_digit(char *num);
long	ph_atol(char *str);
long	ph_gettime_ms(void);
t_philo	*ph_init_philos(t_data *data);

#endif
