/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slangero <slangero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 10:04:04 by student           #+#    #+#             */
/*   Updated: 2024/03/10 10:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>

/* ************************************************************************** */
/*                              CONSTANTS                                      */
/* ************************************************************************** */

# define SUCCESS 0
# define ERROR 1
# define MAX_PHILOSOPHERS 200

/* Error messages */
# define ERR_ARGS "Invalid arguments"
# define ERR_MALLOC "Memory allocation failed"
# define ERR_THREAD "Thread creation failed"
# define ERR_MUTEX "Mutex initialization failed"
# define ERR_TIME "Time function failed"

/* ************************************************************************** */
/*                              STRUCTURES                                     */
/* ************************************************************************** */

typedef struct s_philo	t_philo;

/* Simulation structure */
typedef struct s_simulation
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_goal;
	long long		start_time;
	bool			simulation_ended;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	end_mutex;
	pthread_mutex_t	meal_mutex;
	t_philo			*philos;
}	t_simulation;

/* Philosopher structure */
typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_simulation	*sim;
}	t_philo;

/* ************************************************************************** */
/*                              FUNCTION PROTOTYPES                            */
/* ************************************************************************** */

/* init.c */
int			init_simulation(t_simulation *sim);
int			init_mutexes(t_simulation *sim);
int			init_philosophers(t_simulation *sim);

/* utils.c */
int			ft_atoi(const char *str);
int			error_exit(char *message, t_simulation *sim);
bool		is_valid_number(char *str);
void		cleanup_simulation(t_simulation *sim);
bool		simulation_ended(t_simulation *sim);

/* time.c */
long long	get_current_time(void);
void		precise_sleep(long long ms, t_simulation *sim);
int			set_start_time(t_simulation *sim);

/* philosopher.c */
int			create_philosophers(t_simulation *sim);
void		*philosopher_routine(void *arg);

/* actions.c */
void		take_forks(t_philo *philo);
void		eat(t_philo *philo);
void		release_forks(t_philo *philo);
void		sleep_and_think(t_philo *philo);

/* monitor.c */
void		monitor_simulation(t_simulation *sim);
bool		check_philosopher_death(t_simulation *sim);
bool		check_eating_goal(t_simulation *sim);
void		log_action(t_philo *philo, char *action);

#endif