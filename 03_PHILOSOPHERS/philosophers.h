/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 17:59:46 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/13 18:17:00 by pedromig         ###   ########.fr       */
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
	int	n_philos; // Number of philosophers
	int	mls_die; // Time to die (milisseconds)
	int	mls_eat; // Time to eat (milisseconds)
	int	mls_sleep; // Time to sleep (milisseconds)
	int	n_meals; // Number of meals a philosopher must have (Optional)
}	t_data;

typedef struct s_philo
{
	// To do
}	t_philo;

#endif
