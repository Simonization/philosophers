/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_simulation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:28:07 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:33:00 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_status	init_simulation(t_simulation *sim, int argc, char **argv)
{
	t_status	status;

	sim->allocated_pointers = NULL;
	init_params(argc, argv, sim);
	sim->simulation_ended = false;
	status = init_sim_mutexes(sim);
	if (error(status))
		return (status);
	status = set_simulation_start_time(sim);
	if (error(status))
		return (status);
	status = init_forks_mutexes(sim);
	if (error(status))
		return (status);
	status = init_philosophers(sim);
	if (error(status))
		return (status);
	return (SUCCESS);
}

void	init_params(int argc, char **argv, t_simulation *sim)
{
	sim->nb_philo = ft_atoi(argv[1]);
	sim->time_to_die = ft_atoi(argv[2]);
	sim->time_to_eat = ft_atoi(argv[3]);
	sim->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		sim->eat_goal = ft_atoi(argv[5]);
	else
		sim->eat_goal = -1;
}

t_status	init_forks_mutexes(t_simulation *sim)
{
	int	ret;
	int	i;

	ret = calloc_s((void **)&sim->forks_mutexes, sim->nb_philo
			* sizeof(pthread_mutex_t), sim);
	if (error(ret))
		return (ERROR_ALLOCATION);
	i = 0;
	while (i < sim->nb_philo)
	{
		ret = pthread_mutex_init(&sim->forks_mutexes[i], NULL);
		if (ret != 0)
			return (ERROR_SYSTEM);
		i++;
	}
	return (SUCCESS);
}

t_status	init_sim_mutexes(t_simulation *sim)
{
	memset(sim->mutex, 0, sizeof(pthread_mutex_t) * SIM_MUTEXES);
	if (pthread_mutex_init(&sim->mutex[PRINT], NULL) != SUCCESS)
		return (ERROR_SYSTEM);
	if (pthread_mutex_init(&sim->mutex[END], NULL) != SUCCESS)
		return (ERROR_SYSTEM);
	if (pthread_mutex_init(&sim->mutex[CHECK_MEAL], NULL) != SUCCESS)
		return (ERROR_SYSTEM);
	return (SUCCESS);
}

t_status	init_philosophers(t_simulation *sim)
{
	int	i;
	int	ret;

	ret = calloc_s((void **)&sim->philos, sim->nb_philo * sizeof(t_philosopher),
			sim);
	if (error(ret))
		return (ERROR_ALLOCATION);
	i = 0;
	while (i < sim->nb_philo)
	{
		sim->philos[i].id = i;
		sim->philos[i].meals_eaten = 0;
		sim->philos[i].last_meal = sim->start_time;
		sim->philos[i].sim = sim;
		sim->philos[i].l_fork = &sim->forks_mutexes[i];
		if (i == 0)
			sim->philos[i].r_fork = &sim->forks_mutexes[sim->nb_philo - 1];
		else
			sim->philos[i].r_fork = &sim->forks_mutexes[i - 1];
		i++;
	}
	return (SUCCESS);
}
