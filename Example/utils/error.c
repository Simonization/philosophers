/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:27:45 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:27:46 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

bool	error(t_status status)
{
	if (status != EXIT_SUCCESS)
		return (true);
	return (false);
}

int	report_error(t_status status, t_simulation *sim)
{
	if (status == ERROR_ALLOCATION)
		write(2, "Error: Memory allocation failed\n", 31);
	else if (status == ERROR_SYSTEM)
		write(2, "Error: System call failed\n", 27);
	else if (status == ERROR_ARGUMENTS)
		write(2, "Error: Invalid arguments\n", 26);
	else
		write(2, "Error: Unknown error\n", 22);
	if (sim)
		cleanup_simulation(sim);
	return ((int)status);
}
