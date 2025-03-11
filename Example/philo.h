/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:30:38 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:30:41 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "structs.h"

// Main
int			main(int argc, char **argv);
void		cleanup_simulation(t_simulation *sim);

// Check arguments
t_status	check_arguments(int argc, char **argv);
bool		is_valid_positive_int(char *str);
int			ft_atoi(const char *str);

// Initialize simulation structure
t_status	init_simulation(t_simulation *sim, int argc, char **argv);
void		init_params(int argc, char **argv, t_simulation *sim);
t_status	init_forks_mutexes(t_simulation *sim);
t_status	init_sim_mutexes(t_simulation *sim);
t_status	init_philosophers(t_simulation *sim);

// Launch threads, monitor and join
t_status	run_simulation(t_simulation *sim);
t_status	start_philosopher_threads(t_simulation *sim);
t_status	join_philosopher_threads(t_simulation *sim);

// Philosopher routine
void		*philosopher_routine(void *arg);
bool		simulation_ended(t_simulation *sim);

// Philosopher actions
void		take_forks(t_philosopher *philo);
void		think(t_philosopher *philo);
void		eat(t_philosopher *philo);
void		release_forks(t_philosopher *philo);
void		sleep_philosopher(t_philosopher *philo);

// Monitor simulation
void		monitor_simulation(t_simulation *sim);
bool		check_philosopher_deaths(t_simulation *sim);
bool		check_eating_goal(t_simulation *sim);

// Time related functions
long long	get_time(t_simulation *sim);
t_status	set_simulation_start_time(t_simulation *sim);
void		usleep_precise(size_t milliseconds, t_simulation *sim);

// Logging
void		log_action(int philosopher_id, const char *action,
				t_simulation *sim);

// Utils
// List
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));

// Allocation
t_status	calloc_s(void **pointer, size_t size, t_simulation *sim);
t_status	track_alloc(void *pointer, t_simulation *sim);

// Error handling
bool		error(t_status status);
int			report_error(t_status status, t_simulation *sim);

#endif