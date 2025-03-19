/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:00:00 by student           #+#    #+#             */
/*   Updated: 2025/03/17 23:01:02 by slangero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int		sign;
	long	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if (result * sign > INT_MAX)
			return (INT_MAX);
		if (result * sign < INT_MIN)
			return (INT_MIN);
		str++;
	}
	return (result * sign);
}

bool	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (false);
	if (str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	error_exit(char *message, t_simulation *sim)
{
	if (message)
		printf("Error: %s\n", message);
	if (sim)
		cleanup_simulation(sim);
	return (ERROR);
}

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	if (sim->forks)
	{
		i = 0;
		while (i < sim->nb_philos)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			i++;
		}
		free(sim->forks);
	}
	if (sim->print_mutex_initialized)
		pthread_mutex_destroy(&sim->print_mutex);
	if (sim->end_mutex_initialized)
		pthread_mutex_destroy(&sim->end_mutex);
	if (sim->meal_mutex_initialized)
		pthread_mutex_destroy(&sim->meal_mutex);
	if (sim->philos)
		free(sim->philos);
}

bool	simulation_ended(t_simulation *sim)
{
	bool	ended;

	pthread_mutex_lock(&sim->end_mutex);
	ended = sim->simulation_ended;
	pthread_mutex_unlock(&sim->end_mutex);
	return (ended);
}
