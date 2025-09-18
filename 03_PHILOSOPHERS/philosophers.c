/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 22:39:46 by pedromig          #+#    #+#             */
/*   Updated: 2025/09/18 15:50:23 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data 	data;
	t_philo	philos[200];

	if (ph_init_data(argc, argv, &data) == -1)
		return (1); // Couldn't initiate data; Cleanup left;
	ph_init_philos(&data, philos);
	data.start_time = ph_gettime_ms();
	printf("DBG: start_time=%ld\n", data.start_time);
	for (int i = 0; i < data.n_philos; ++i)
    	printf("DBG: init philo[%d].time_last_meal=%ld\n", i+1, philos[i].time_last_meal);
	ph_create_threads(philos);
	ph_join_threads(philos);
}
