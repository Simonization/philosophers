/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:30:49 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:31:42 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

// UTILS
// List
typedef struct s_list
{
	void						*content;
	struct s_list				*next;
	struct s_list				*prev;
}								t_list;
// Error codes
typedef enum t_status
{
	SUCCESS,
	ERROR_ALLOCATION,
	ERROR_SYSTEM,
	ERROR_ARGUMENTS,
	THREAD_CREATION_ERROR,
	THREAD_JOIN_ERROR
}								t_status;

typedef enum t_alloc
{
	ONLY_CHECK,
	TRACK
}								t_alloc;

// PHILO
#define MAX_PHILOSOPHERS 200
#define MIN_TIME 60

#define SIM_MUTEXES 3

typedef enum t_sim_mutex
{
	PRINT,
	END,
	CHECK_MEAL
}								t_sim_mutex;

typedef struct s_philosopher	t_philosopher;

typedef struct s_simulation
{
	t_list						*allocated_pointers;
	int							nb_philo;
	int							time_to_die;
	int							time_to_eat;
	int							time_to_sleep;
	int							eat_goal;
	bool						simulation_ended;
	long long					start_time;
	pthread_mutex_t				mutex[SIM_MUTEXES];
	pthread_mutex_t				*forks_mutexes;
	t_philosopher				*philos;
}								t_simulation;

typedef struct s_philosopher
{
	int							id;
	int							meals_eaten;
	long long					last_meal;
	pthread_t					thread;
	t_simulation				*sim;
	pthread_mutex_t				*r_fork;
	pthread_mutex_t				*l_fork;
}								t_philosopher;
