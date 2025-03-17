/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:09:11 by student           #+#    #+#             */
/*   Updated: 2024/03/10 10:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	validate_arguments(int ac, char **av)
{
	int	i;

	if (ac != 5 && ac != 6)
		return (ERROR);
	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (ERROR);
		if (ft_atoi(av[i]) <= 0)
			return (ERROR);
		if (i == 1 && ft_atoi(av[i]) > MAX_PHILOSOPHERS)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	parse_arguments(t_simulation *sim, int ac, char **av)
{
	sim->nb_philos = ft_atoi(av[1]);
	sim->time_to_die = ft_atoi(av[2]);
	sim->time_to_eat = ft_atoi(av[3]);
	sim->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		sim->meals_goal = ft_atoi(av[5]);
	else
		sim->meals_goal = -1;
	return (SUCCESS);
}

int	run_simulation(t_simulation *sim)
{
	if (set_start_time(sim) != SUCCESS)
		return (error_exit(ERR_TIME, sim));
	if (create_philosopher_threads(sim) != SUCCESS)
		return (error_exit(ERR_THREAD, sim));
	monitor_simulation(sim);
	if (join_philosopher_threads(sim) != SUCCESS)
		return (error_exit(ERR_THREAD, sim));
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	t_simulation	sim;

	if (validate_arguments(ac, av) != SUCCESS)
		return (error_exit(ERR_ARGS, NULL));
	memset(&sim, 0, sizeof(t_simulation));
	if (parse_arguments(&sim, ac, av) != SUCCESS)
		return (error_exit(ERR_ARGS, NULL));
	if (init_simulation(&sim) != SUCCESS)
		return (ERROR);
	if (run_simulation(&sim) != SUCCESS)
		return (ERROR);
	cleanup_simulation(&sim);
	return (SUCCESS);
}
