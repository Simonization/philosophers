/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:30:29 by student           #+#    #+#             */
/*   Updated: 2024/03/10 10:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_simulation(t_simulation *sim)
{
	sim->simulation_ended = false;
	if (init_mutexes(sim) != SUCCESS)
		return (ERROR);
	if (init_philosophers(sim) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int	init_mutexes(t_simulation *sim)
{
	int	i;

	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->nb_philos);
	if (!sim->forks)
		return (error_exit(ERR_MALLOC, sim));
	i = 0;
	while (i < sim->nb_philos)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL) != 0)
			return (error_exit(ERR_MUTEX, sim));
		i++;
	}
	if (pthread_mutex_init(&sim->print_mutex, NULL) != 0)
		return (error_exit(ERR_MUTEX, sim));
	if (pthread_mutex_init(&sim->end_mutex, NULL) != 0)
		return (error_exit(ERR_MUTEX, sim));
	if (pthread_mutex_init(&sim->meal_mutex, NULL) != 0)
		return (error_exit(ERR_MUTEX, sim));
	return (SUCCESS);
}

int	init_philosophers(t_simulation *sim)
{
	int	i;

	sim->philos = malloc(sizeof(t_philo) * sim->nb_philos);
	if (!sim->philos)
		return (error_exit(ERR_MALLOC, sim));
	i = 0;
	while (i < sim->nb_philos)
	{
		sim->philos[i].id = i;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].last_meal_time = 0;
		sim->philos[i].sim = sim;
		sim->philos[i].right_fork = &sim->forks[i];
		if (i == 0)
			sim->philos[i].left_fork = &sim->forks[sim->nb_philos - 1];
		else
			sim->philos[i].left_fork = &sim->forks[i - 1];
		i++;
	}
	return (SUCCESS);
}
