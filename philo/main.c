/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:02:20 by gro-donn          #+#    #+#             */
/*   Updated: 2025/02/25 15:20:27 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// KEEP TRACK OF HOW LONG THE PHILOS WAITED TO GET A LOCK TO FIGURE OUT WHATS HAPPENING

int	check_die(t_philo *philos, t_params *params)
{
	size_t	time_since_last_meal;

	pthread_mutex_lock(&philos->meal_lock);
	time_since_last_meal = get_current_time() - philos->last_meal_time ;
	pthread_mutex_unlock(&philos->meal_lock);

   // printf("Philosopher %d: Time since last meal: %zu,\n",
          // philos->id, time_since_last_meal);
	return (time_since_last_meal >= (params->time_until_die +1));
}

//usleep(5000); // Small delay to reduce CPU usage
// 	if (!philos[i].is_finished) to make sure i only count it once 	
int	monitor_die(t_philo *philos, t_params *params)
{
	int	finished_philos;
	int	simulation_running;

	finished_philos = 0;
	simulation_running = 1;
	while (simulation_running) 
	{	
    for (int i = 0; i < params->total_philos; i++)
		{
			if (check_die(&philos[i], params))
			{
                printf("Philosopher %d died while holding fork? %d\n", philos[i].id, philos[i].is_holding_fork);
				die(&philos[i]);
				simulation_running = 0;
				return (-51);  // Stop simulation immediately
			}
			// **Check if philosopher has finished eating**
			pthread_mutex_lock(&philos[i].meal_lock);
			if (params->total_num_need_eats != -1 && philos[i].meals_eaten >= params->total_num_need_eats)
			{
				if (!philos[i].is_finished)
				{
					philos[i].is_finished = 1;
					finished_philos++;
				}
			}
			pthread_mutex_unlock(&philos[i].meal_lock);
		}
		if (params->total_num_need_eats != -1 && finished_philos == params->total_philos)
		{
			simulation_running = 0;
			return (0);
		}
		usleep(5000); 
	}
	return (0);
}


void	*routine(void *arg)
{
	int	meals_eaten;
	t_philo *philos = (t_philo *)arg;  // Cast the argument back to t_philo
	t_params *params = philos->params; // Get params from philos struct
	meals_eaten = 0;

	while (1)
	{
        if (check_die(philos, params) == 1)
			die(philos);
		eat(philos, params);
        if (check_die(philos, params) == 1)
			die(philos);
		philo_sleep(philos, params);
        if (check_die(philos, params) == 1)
			die(philos);
		think(philos);
		meals_eaten++;
        if (params->total_num_need_eats != -1 && meals_eaten >= params->total_num_need_eats)
			break ;
	}
	return (NULL);
}

// pthread_mutex_t is a data type that represents a mutex (mutual exclusion) object.
int	main(int ac, char **av)
{
	t_philo			philos[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];
	t_params		params;
	int				total_philos;

	if (ac < 5 || ac > 6)
	{
		write(2, "Incorrect number of arguments \n", 31);
		return (-2);
	}
	if (check_args(av) == 1)
		return (-3);
	init_params(&params, av);
	total_philos = params.total_philos;
	init_forks_mutexes(forks, total_philos, philos);
	init_philos(philos, forks, &params);

 for (int i = 0; i < total_philos; i++)
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);

	if (params.total_num_need_eats == -1)
	{
		if (monitor_die(philos, &params))
			return (0);
	}
	else
	{
		while (1)
		{
			int finished_philos = 0;
			for (int i = 0; i < total_philos; i++)
			{
				pthread_mutex_lock(&philos[i].meal_lock);
				if (philos[i].meals_eaten >= params.total_num_need_eats)
					finished_philos++;
				pthread_mutex_unlock(&philos[i].meal_lock);
			}
			if (finished_philos == total_philos)
				break;
			usleep(200);
		}
	}
	// **Wait for all threads to finish**
	for (int i = 0; i < total_philos; i++)
		pthread_join(philos[i].thread, NULL);

	for (int i = 0; i < total_philos; i++)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].meal_lock);
	}

	for (int i = 0; i < total_philos; i++)
	{
		printf("Philosopher %d ate %d times.\n", philos[i].id, philos[i].meals_eaten);
	}

}

/*
PTHREAD CREATE
 Spawns all philosophers as independent threads, running in parallel.
NULL: This argument specifies the thread attributes.
Passing NULL means that the thread will have default attributes.
&philos[i].thread = address of thread id
: This is a pointer to the function that the thread will execute.
&philos[i]: This is a pointer to the philosopher structure that will be passed as an argument to the routine function.

PTHREAD JOIN
Second loop: Waits for all threads to finish execution.
. The second argument is used to retrieve the return value of the thread,
 pthread_join prevents the program from closing early by ensuring
 the main thread waits for all philosopher threads to finish.

Each thread will receive its corresponding philosopher's data.
A thread is a routine running in background until terminated or interrupted.
Threads share resources, and have access to resources once at a time.

Real life example: mobiles can play music and receive notifications; the music player
 and the notification app both share the resource sound: when receiving a message,
	the music player stops for a sec,
	the notification rings and then frees the resource sound again.

In philosophers, each person has a thread routine (eat-sleep-think),
	and forks are the shared resources.
To avoid forks being used by more philosophers at once,
	we block the access with mutex_lock(),
	and we mutex_unlock() when we are done.
tv_sec: seconds since epoch (January 1, 1970) struct timeval {
	time_t      tv_sec;   // Seconds since January 1, 1970 (Epoch time)};
*/
/*
pthread_join(pthread_t thread, void **retval)
Waits for a thread to finish execution.

The return value of the thread (if any) is stored in retval.
Use case: Ensuring a thread completes before the program continues.
pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr)
pthread_mutex_lock(pthread_mutex_t *mutex)
Locks a mutex.

If another thread already locked it, the calling thread waits.
It's possible that Philosopher 2 had just started eating, but the monitor 
thread checked right before the last_meal_time update.
If so, this is a race condition where Philosopher 2 was actually eating, 
but the program thought they were still starving.

Race Condition:

There might be a race condition between updating the last_meal_time and checking 
for death. If the check_die function runs just after the philosopher picks up the forks but before they update their last_meal_time,
 it could incorrectly determine that the philosopher has starved.
*/
