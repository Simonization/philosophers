/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:28:15 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:28:16 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	log_action(int philosopher_id, const char *action, t_simulation *sim)
{
	long long	current_time;

	current_time = get_time(sim) - sim->start_time;
	if (current_time == -1)
		return ;
	pthread_mutex_lock(&sim->mutex[PRINT]);
	if (!simulation_ended(sim))
		printf("%lld %d %s\n", current_time, philosopher_id + 1, action);
	pthread_mutex_unlock(&sim->mutex[PRINT]);
}
