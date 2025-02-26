/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:02:20 by gro-donn          #+#    #+#             */
/*   Updated: 2025/02/26 09:36:18 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// KEEP TRACK OF HOW LONG PHILOS WAITED TO GET A LOCK TO FIGURE WHATS HAPPENING

// pthread_mutex_t= a data type that represents a mutex (mutual exclusion) obj

void	print_results(t_philo *philos, int total_philos)
{
	int	i;

	i = 0;
	while (i < total_philos)
	{
		printf("Philosopher %d ate %d times.\n", philos[i].id,
			philos[i].meals_eaten);
		i++;
	}
}

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
}

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

// int monitor_philos(t_philo *philos, t_params *params)
// {
//     if (params->total_num_need_eats == -1)
//      {
//         return (monitor_die(philos, params));
//     }
//     else
//     {
//         while (1)
//         {
//             int finished_philos = 0;
//             for (int i = 0; i < params->total_philos; i++)
//             {
//                 pthread_mutex_lock(&philos[i].meal_lock);
//                 if (philos[i].meals_eaten >= params->total_num_need_eats)
//                 {
//                     finished_philos++;
//                 }
//                 pthread_mutex_unlock(&philos[i].meal_lock);
//             }
//             if (finished_philos == params->total_philos) {
//                 break ;
//             }
//             usleep(200);
//         }
//     }
//     return (0);
// }

int	main(int ac, char **av)
{
	t_philo			philos[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];
	t_params		params;
	int				total_philos;
	int				i;
	int				finished_philos;

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
	i = 0;
	while (i < total_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	if (params.total_num_need_eats == -1)
	{
		if (monitor_die(philos, &params))
			return (0);
	}
	else
	{
		while (1)
		{
			finished_philos = 0;
			i = 0;
			while (i < total_philos)
			{
				pthread_mutex_lock(&philos[i].meal_lock);
				if (philos[i].meals_eaten >= params.total_num_need_eats)
					finished_philos++;
				pthread_mutex_unlock(&philos[i].meal_lock);
				i++;
			}
			if (finished_philos == total_philos)
				break ;
			usleep(200);
		}
	}
	create_philo_threads(philos, params.total_philos);
	// monitor_philos(philos, &params);
	cleanup_resources(philos, forks, params.total_philos);
		// NEED TO CHECK WITH HELGRIND AT THE MOMENT IM BLIND
	print_results(philos, params.total_philos);
	return (0);
}

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
