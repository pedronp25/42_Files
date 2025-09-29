/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:59:46 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/29 19:35:56 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_PHILOS 200

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

typedef struct s_data
{
	long			n_philos; // Number of philosophers
	long			time_die; // Time to die (milisseconds)
	long			time_eat; // Time to eat (milisseconds)
	long			time_sleep; // Time to sleep (milisseconds)
	long			n_meals; // Number of meals a philosopher must have (Optional)
	
	long			start_time; // Start time in milisseconds
	
	pthread_mutex_t	forks[MAX_PHILOS];
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;

	pthread_t		monitor;
	int				simulation_over;

}	t_data;

typedef struct s_philo
{
	int				id; // This philosopher's ID
	int				meals_eaten; // Number of meals eaten for this philosopher
	long			time_last_meal; // Timestamp of last meal eaten
	
	pthread_t		thread; // This philosopher's thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;

	pthread_mutex_t	meal_mutex;

	//int				is_eating;

	t_data			*data;

}	t_philo;


int		ph_init_data(int argc, char **argv, t_data *data);
int		ph_validate_arguments(int argc, char **argv, t_data *data);
int		ph_is_digit(char *num);
long	ph_atol(char *str);
void	ph_init_philos(t_data *data, t_philo *philos);
long	ph_gettime_ms(void);
long	ph_elapsedtime(t_philo *philos);
void	ph_create_threads(t_philo *philos);
void	ph_join_threads(t_philo *philos);
void	*ph_routine(void *arg);
void	*ph_monitor(void *arg);
void	ph_check_meals(t_philo *philos, int	*n_philos_full);
void	ph_print(t_philo *philos, int id, char *msg);
int		ph_eat(t_philo *philos);
void	ph_take_fork(t_philo *philos);
void	ph_putdown_fork(t_philo *philos);
int		ph_sleep_and_think(t_philo *philos);
void    ph_split_usleep(t_philo *philos, long ms);
int		ph_is_dead(t_philo *philos);
int		ph_get_sim_over(t_data *data);
void	ph_set_sim_over(t_data *data);
long	ph_get_time_last_meal(t_philo *philos);
//int		ph_get_is_eating(t_philo *philos);
void	ph_set_time_last_meal(t_philo *philos, long new_time);
int		ph_get_meals_eaten(t_philo *philos);
void	ph_inc_meals_eaten(t_philo *philos);
void	ph_set_meals_eaten(t_philo *philos, int value);
void	ph_cleanup(t_philo *philos);

#endif
