/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:28:27 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:45:05 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

/**
	@brief Monitor simulation and check philosopher's state
	@note This a blocking function that will run until the simulation ends
	@note To avoid CPU overload, it will sleep for 1 microsecond
*/
void	monitor_simulation(t_simulation *sim)
{
	bool	simulation_running;

	simulation_running = true;
	while (simulation_running)
	{
		pthread_mutex_lock(&sim->mutex[CHECK_MEAL]);
		if (check_philosopher_deaths(sim) || check_eating_goal(sim))
			simulation_running = false;
		pthread_mutex_unlock(&sim->mutex[CHECK_MEAL]);
		usleep_precise(1, sim);
	}
}

bool	check_philosopher_deaths(t_simulation *sim)
{
	long long	current_time;
	int			i;

	current_time = get_time(sim);
	if (current_time == -1)
		return (true);
	i = 0;
	while (i < sim->nb_philo)
	{
		if (current_time - sim->philos[i].last_meal > sim->time_to_die)
		{
			log_action(sim->philos[i].id, "died", sim);
			pthread_mutex_lock(&sim->mutex[END]);
			sim->simulation_ended = true;
			pthread_mutex_unlock(&sim->mutex[END]);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_eating_goal(t_simulation *sim)
{
	int	i;

	if (sim->eat_goal == -1)
		return (false);
	i = 0;
	while (i < sim->nb_philo)
		if (sim->philos[i++].meals_eaten < sim->eat_goal)
			return (false);
	pthread_mutex_lock(&sim->mutex[END]);
	sim->simulation_ended = true;
	pthread_mutex_unlock(&sim->mutex[END]);
	return (true);
}
