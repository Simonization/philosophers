/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:08:43 by student           #+#    #+#             */
/*   Updated: 2024/03/10 10:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	monitor_simulation(t_simulation *sim)
{
	bool	should_continue;

	should_continue = true;
	while (should_continue)
	{
		pthread_mutex_lock(&sim->meal_mutex);
		if (check_philosopher_death(sim) || check_eating_goal(sim))
			should_continue = false;
		pthread_mutex_unlock(&sim->meal_mutex);
		usleep(1000);
	}
}

bool	check_philosopher_death(t_simulation *sim)
{
	int			i;
	long long	current_time;
	long long	time_since_last_meal;

	current_time = get_current_time();
	if (current_time == -1)
		return (true);
	i = 0;
	while (i < sim->nb_philos)
	{
		time_since_last_meal = current_time - sim->philos[i].last_meal_time;
		if (time_since_last_meal > sim->time_to_die)
		{
			pthread_mutex_lock(&sim->end_mutex);
			sim->simulation_ended = true;
			pthread_mutex_unlock(&sim->end_mutex);
			pthread_mutex_lock(&sim->print_mutex);
			printf("%lld %d died\n", 
				current_time - sim->start_time, sim->philos[i].id + 1);
			pthread_mutex_unlock(&sim->print_mutex);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_eating_goal(t_simulation *sim)
{
	int	i;

	if (sim->meals_goal == -1)
		return (false);
	i = 0;
	while (i < sim->nb_philos)
	{
		if (sim->philos[i].meals_eaten < sim->meals_goal)
			return (false);
		i++;
	}
	pthread_mutex_lock(&sim->end_mutex);
	sim->simulation_ended = true;
	pthread_mutex_unlock(&sim->end_mutex);
	return (true);
}

void	log_action(t_philo *philo, char *action)
{
	long long	timestamp;

	if (simulation_ended(philo->sim))
		return;
	timestamp = get_current_time() - philo->sim->start_time;
	pthread_mutex_lock(&philo->sim->print_mutex);
	if (!simulation_ended(philo->sim))
		printf("%lld %d %s\n", timestamp, philo->id + 1, action);
	pthread_mutex_unlock(&philo->sim->print_mutex);
}