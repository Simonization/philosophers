/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 20:39:52 by student           #+#    #+#             */
/*   Updated: 2025/03/17 21:33:46 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_philosopher_threads(t_simulation *sim)
{
	int	i;
	int	ret;

	i = 0;
	while (i < sim->nb_philos)
	{
		sim->philos[i].last_meal_time = sim->start_time;
		ret = pthread_create(&sim->philos[i].thread, NULL,
				philosopher_routine, &sim->philos[i]);
		if (ret != 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int	join_philosopher_threads(t_simulation *sim)
{
	int	i;
	int	ret;

	i = 0;
	while (i < sim->nb_philos)
	{
		ret = pthread_join(sim->philos[i].thread, NULL);
		if (ret != 0)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_sleep(10, philo->sim);
	pthread_mutex_lock(&philo->sim->meal_mutex);
	philo->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philo->sim->meal_mutex);
	while (!simulation_ended(philo->sim))
	{
		if (philo->sim->nb_philos == 1)
		{
			log_action(philo, "has taken a fork");
			precise_sleep(philo->sim->time_to_die, philo->sim);
			break ;
		}
		take_forks(philo);
		eat(philo);
		release_forks(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
