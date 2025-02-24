/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:02:32 by gro-donn          #+#    #+#             */
/*   Updated: 2025/02/21 11:36:40 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>   //gettimeofday

#define PHILOS_MAX 200

typedef struct s_params
{
    int	total_philos;
    int	total_num_need_eats;  
    size_t duration_eating; 
    size_t duration_sleeping;
    size_t time_until_die;
    pthread_mutex_t sim_lock; 
	int simulation_running;  
} t_params;

typedef struct s_philo 
{
    int id;
    int meals_eaten;
    size_t last_meal_time;
    size_t	start_time;  
    int	is_dead;
    int is_holding_fork;
    int is_finished;
    pthread_t thread;
    pthread_mutex_t	*r_fork;   //these have to be ptrs to pthread mutex not values!
    // ! otherwise  This creates a separate mutex for each philosopher which would defeat the 
    // whole purpse
	pthread_mutex_t	*l_fork; 
     t_params *params; // pthread_create allows only one argument, add a t_params *params field in t_philo:
    pthread_mutex_t meal_lock; ///stale mealtimes leading to wrong deaths NTO A PTR WHY??
   
} t_philo;

int	ft_atoi(char *str);
size_t get_current_time(void);
void print_human_readable_time(size_t milliseconds);
void	init_philos(t_philo *philos, pthread_mutex_t *forks, t_params *params);
void	init_forks_mutexes(pthread_mutex_t *forks, int total_philos,
		t_philo *philos);
void	init_params(t_params *params, char **av);
int	check_args(char **av);
int	is_digit(char *av);

#endif //PHILO_H