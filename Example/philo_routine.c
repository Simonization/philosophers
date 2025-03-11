/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:28:37 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:28:38 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
	@brief Philosopher routine to execute actions
	@note To avoid deadlock,
		even philosophers wait 1 microsecond before starting
*/
void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->id % 2 == 0)
		usleep_precise(1, philo->sim);
	while (!simulation_ended(philo->sim))
	{
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_philosopher(philo);
		think(philo);
	}
	return (NULL);
}

bool	simulation_ended(t_simulation *sim)
{
	bool	ended;

	pthread_mutex_lock(&sim->mutex[END]);
	ended = sim->simulation_ended;
	pthread_mutex_unlock(&sim->mutex[END]);
	return (ended);
}
