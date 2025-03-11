/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:28:41 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:28:42 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_status	run_simulation(t_simulation *sim)
{
	t_status	status;

	status = start_philosopher_threads(sim);
	if (error(status))
		return (status);
	monitor_simulation(sim);
	status = join_philosopher_threads(sim);
	if (error(status))
		return (status);
	return (SUCCESS);
}

t_status	start_philosopher_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philo)
	{
		if (pthread_create(&sim->philos[i].thread, NULL, philosopher_routine,
				&sim->philos[i]) != SUCCESS)
			return (THREAD_CREATION_ERROR);
		i++;
	}
	return (SUCCESS);
}

t_status	join_philosopher_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->nb_philo)
	{
		if (pthread_join(sim->philos[i].thread, NULL) != SUCCESS)
			return (THREAD_JOIN_ERROR);
		i++;
	}
	return (SUCCESS);
}
