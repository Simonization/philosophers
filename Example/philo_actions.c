/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:28:32 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:28:33 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->r_fork);
	log_action(philo->id, "has taken a fork", philo->sim);
	if (philo->sim->nb_philo == 1)
	{
		usleep_precise(philo->sim->time_to_die + 1, philo->sim);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	log_action(philo->id, "has taken a fork", philo->sim);
}

void	eat(t_philosopher *philo)
{
	t_simulation	*sim;

	sim = philo->sim;
	log_action(philo->id, "is eating", sim);
	pthread_mutex_lock(&philo->sim->mutex[CHECK_MEAL]);
	philo->last_meal = get_time(philo->sim);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->sim->mutex[CHECK_MEAL]);
	usleep_precise(sim->time_to_eat, sim);
}

void	release_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_philosopher(t_philosopher *philo)
{
	log_action(philo->id, "is sleeping", philo->sim);
	usleep_precise(philo->sim->time_to_sleep, philo->sim);
}

void	think(t_philosopher *philo)
{
	log_action(philo->id, "is thinking", philo->sim);
}
