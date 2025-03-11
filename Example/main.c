/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:28:22 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:28:24 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

int	main(int argc, char **argv)
{
	t_simulation	sim;
	t_status		status;

	status = check_arguments(argc, argv);
	if (error(status))
		return (report_error(status, NULL));
	status = init_simulation(&sim, argc, argv);
	if (error(status))
		return (report_error(status, &sim));
	status = run_simulation(&sim);
	if (error(status))
		return (report_error(status, &sim));
	cleanup_simulation(&sim);
	return ((int)status);
}

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < SIM_MUTEXES)
		if (&sim->mutex[i])
			pthread_mutex_destroy(&sim->mutex[i++]);
	i = 0;
	while (i < sim->nb_philo)
		if (&sim->forks_mutexes[i])
			pthread_mutex_destroy(&sim->forks_mutexes[i++]);
	ft_lstclear(&sim->allocated_pointers, free);
}
