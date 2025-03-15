/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:02:32 by gro-donn          #+#    #+#             */
/*   Updated: 2025/03/12 16:45:53 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h> //gettimeofday
# include <unistd.h>

# define PHILOS_MAX 200

// its a shared flag to indicate so need mutex
typedef struct s_params
{
	int				total_philos;
	int				num_eats;
	size_t			duration_eating;
	size_t			duration_sleeping;
	size_t			time_until_die;
	int				simulation_running;
	pthread_mutex_t	sim_lock;

}					t_params;

// these have to be ptrs to pthread mutex not values!
// ! otherwise  This creates a separate mutex for each philosopher which
// would defeat the whole purpse
// pthread_create allows only one argument,
//	add a t_params *params field in t_philo:
// no ptr for meal_lock cos each philosopher(t_philo)
//  has its own meal_lock that is not shared with other philosophers.
// but still need it to be a mutex because it protects
// mealseaten or lastmealtime
// could have a global mutex but this would lock all philos data
// and reduce parallelism
// forks are shared among philosophers, so they are stored in a separate arr,
// and each philosopher holds pointers to the shared forks.

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	size_t			last_meal_time;
	size_t			start_time;
	int				is_dead;
	int				is_holding_fork;
	int				is_finished;
	pthread_t		thread;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_params		*params;
	pthread_mutex_t	meal_lock;
}					t_philo;

int					ft_atoi(char *str);
int					is_digit(char *av);
int					check_args(char **av);
int					safe_print(t_philo *philo, char *msg);

size_t				get_current_time(void);
void				print_results(t_philo *philos, int total_philos);
void				init_philos(t_philo *philos, pthread_mutex_t *forks,
						t_params *params);
void				init_forks_mutexes(pthread_mutex_t *forks, int total_philos,
						t_philo *philos);
void				init_params(t_params *params, char **av);

void				think(t_philo *philos);
void				philo_sleep(t_philo *philos, t_params *params);
void				*routine(void *arg);
void				eat(t_philo *philos, t_params *params);

void				die(t_philo *philos);
int					check_die(t_philo *philos, t_params *params);
int					monitor_die(t_philo *philos, t_params *params);

void				create_philo_threads(t_philo *philos, int total_philos);
void				cleanup_resources(t_philo *philos, pthread_mutex_t *forks,
						int total_philos);

#endif // PHILO_H