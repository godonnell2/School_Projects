/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:02:20 by gro-donn          #+#    #+#             */
/*   Updated: 2025/03/12 18:25:14 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// KEEP TRACK OF HOW LONG PHILOS WAITED TO GET A LOCK TO FIGURE WHATS HAPPENING
// pthread_mutex_t= a data type that represents a mutex (mutual exclusion) obj
// pthread_join =waits until each thread finishes, then we can clean up safely
// If you don’t join threads, their resources (e.g., stack memory)
// may not be properly released, leading to memory leaks.
// otherwise The main thread  will prob proceed to destroy mutexes while philo
// threads are still running, causing crashes or undefined behavior.
void	cleanup_resources(t_philo *philos, pthread_mutex_t *forks,
		int total_philos)
{
	int	i;

	i = 0;
	while (i < total_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < total_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&philos[0].params->sim_lock);
}

// usleep(100);
// was told to do this but i think it's a bit hacky and uncessary
// the proper synchronization with mutexes should be enough
// Small delay to avoid race condition during startup
void	create_philo_threads(t_philo *philos, int total_philos)
{
	int	i;

	i = 0;
	while (i < total_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_philo			philos[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];
	t_params		params;

	if (ac < 5 || ac > 6)
		return (write(2, "Incorrect number of arguments\n", 30));
	if (check_args(av) == 1)
		return (-3);
	init_params(&params, av);
	pthread_mutex_init(&params.sim_lock, NULL);
	params.simulation_running = 1;
	init_forks_mutexes(forks, params.total_philos, philos);
	init_philos(philos, forks, &params);
	create_philo_threads(philos, params.total_philos);
	if (monitor_die(philos, &params) != 0)
	{
		pthread_mutex_lock(&params.sim_lock);
		params.simulation_running = 0;
		pthread_mutex_unlock(&params.sim_lock);
	}
	cleanup_resources(philos, forks, params.total_philos);
	return (0);
}
// if (monitor_die(philos, &params) != 0)
// A philosopher died, simulation ends
/*
PTHREAD CREATE
 Spawns all philosophers as independent threads, running in parallel.
NULL: This argument specifies the thread attributes.
Passing NULL means that the thread will have default attributes.
&philos[i].thread = address of thread id
: This is a pointer to the function that the thread will execute.
&philos[i]: This is a pointer to the philosopher structure that
 will be passed as an argument to the routine function.

PTHREAD JOIN
Second loop: Waits for all threads to finish execution.
. The second argument is used to retrieve the return value of the thread,
 pthread_join prevents the program from closing early by ensuring
 the main thread waits for all philosopher threads to finish.

Each thread will receive its corresponding philosopher's data.
A thread is a routine running in background until terminated or interrupted.
Threads share resources, and have access to resources once at a time.

example: mobiles can play music and receive notifications; music player
 and the notification app both share the resource sound: when receiving a msg,
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
for death. If the check_die function runs just after the philosopher picks up
the forks but before they update their last_meal_time,
 it could incorrectly determine that the philosopher has starved.
*/
