/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:28:33 by student           #+#    #+#             */
/*   Updated: 2024/03/10 10:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long long	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	precise_sleep(long long ms, t_simulation *sim)
{
	long long	start;
	long long	elapsed;

	start = get_current_time();
	if (start == -1)
		return ;
	while (!simulation_ended(sim))
	{
		elapsed = get_current_time() - start;
		if (elapsed >= ms)
			break ;
		usleep(500);
	}
}

int	set_start_time(t_simulation *sim)
{
	sim->start_time = get_current_time();
	if (sim->start_time == -1)
		return (ERROR);
	return (SUCCESS);
}
