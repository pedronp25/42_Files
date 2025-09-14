/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:59:46 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/14 18:54:48 by pedromig         ###   ########.fr       */
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
	int		n_philos; // Number of philosophers
	int		time_die; // Time to die (milisseconds)
	int		time_eat; // Time to eat (milisseconds)
	int		time_sleep; // Time to sleep (milisseconds)
	int		n_meals; // Number of meals a philosopher must have (Optional)
	
	int		is_dead; // Value to stop simulation when someone dies
	long	start_time; // Start time in milisseconds
}	t_data;

typedef struct s_philo
{
	// To do
}	t_philo;

#endif
