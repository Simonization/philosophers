/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:28:44 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:42:47 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

long long	get_time(t_simulation *sim)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) != SUCCESS)
	{
		pthread_mutex_lock(&sim->mutex[END]);
		sim->simulation_ended = true;
		pthread_mutex_unlock(&sim->mutex[END]);
		pthread_mutex_lock(&sim->mutex[PRINT]);
		report_error(ERROR_SYSTEM, NULL);
		pthread_mutex_unlock(&sim->mutex[PRINT]);
		return (-1);
	}
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

/**
	@brief A more precise sleep function than usleep
	@note Uses repeated short-duration sleeps to allow more accurate wake times 
	by minimizing the overshoot that can occur with longer sleep intervals.
 */
void	usleep_precise(size_t milliseconds, t_simulation *sim)
{
	long long	start;

	start = get_time(sim);
	if (start == -1)
		return ;
	while ((get_time(sim) - start) < (long long)milliseconds)
		usleep(500);
}

t_status	set_simulation_start_time(t_simulation *sim)
{
	struct timeval	timeval;

	if (gettimeofday(&timeval, NULL) != SUCCESS)
		return (ERROR_SYSTEM);
	sim->start_time = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (SUCCESS);
}
