/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:02:20 by gro-donn          #+#    #+#             */
/*   Updated: 2025/02/24 15:08:04 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// KEEP TRACK OF HOW LONG THE PHILOS WAITED TO GET A LOCK TO FIGURE OUT WHATS HAPPENING

void	think(t_philo *philos)
{
	size_t	time_ms;

	time_ms = get_current_time();
	printf("%zu %d is thinking\n", time_ms, philos->id);
}

/*
it reduces CPU usage
*/
void	philo_sleep(t_philo *philos, t_params *params)
{
	size_t	start_time_ms;

	start_time_ms = get_current_time();
	printf("%zu %d is sleeping\n", start_time_ms, philos->id);
	while ((get_current_time() - start_time_ms) < params->duration_sleeping)
	{
		usleep(100);
	}
}

void	die(t_philo *philos)
{
	size_t	time_ms;
    time_ms = get_current_time();
printf("Philosopher %d died. Last meal time: %zu, Current time: %zu, Time since last meal: %zu\n",
       philos->id, philos->last_meal_time, get_current_time(), get_current_time() - philos->last_meal_time);
	
	philos->is_dead = 1;
	printf("%zu %d died\n", time_ms, philos->id);
}

/*
Even though each philosopher follows a strict eat → sleep → think cycle,
they are running in parallel on separate threads.
 Without proper synchronization, multiple philosophers could:
 Modify meals_eaten at the same time, causing race conditions.
Read/write last_meal_time while another philosopher (or a monitor thread)
 is checking it, leading to inconsistencies.
Since	usleep(void) expects microseconds, we need to convert
 milliseconds to microseconds by multiplying by 1000.
 no and needed for locking because the forks are already ptrs
  // Avoid deadlock: Odd philosophers pick right fork first!!!!!
  otherwise everyone grabs left fork and prog stalls
Delay before second fork: Allows slight desynchronization to avoid two adjacent philosophers competing at the exact same time.
✅ Immediate last_meal_time update: Ensures the death check mechanism doesn't falsely detect starvation due to a delayed update.
*/
//all odd philos have a tiny eat at the beginning 
void eat(t_philo *philos, t_params *params) {
    size_t start_time_ms = get_current_time();

    if (params->total_philos == 1) {
        pthread_mutex_lock(philos->l_fork);
        printf("%zu %d has taken a fork\n", start_time_ms, philos->id);
        usleep(params->time_until_die * 1000);
        pthread_mutex_unlock(philos->l_fork);
        die(philos);
        return;
    }

    if (philos->id % 2 == 1) {
        pthread_mutex_lock(philos->r_fork);
        printf("%zu %d has taken a fork\n", get_current_time(), philos->id);
        pthread_mutex_lock(philos->l_fork);
        printf("%zu %d has taken a fork\n", get_current_time(), philos->id);
    } else {
        pthread_mutex_lock(philos->l_fork);
        printf("%zu %d has taken a fork\n", get_current_time(), philos->id);
        pthread_mutex_lock(philos->r_fork);
        printf("%zu %d has taken a fork\n", get_current_time(), philos->id);
    }

    // Update last_meal_time before eating
    pthread_mutex_lock(&philos->meal_lock);
    philos->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philos->meal_lock);

    printf("%zu %d is eating\n", start_time_ms, philos->id);
    usleep(params->duration_eating * 1000); // Simulate eating

    pthread_mutex_lock(&philos->meal_lock);
    philos->meals_eaten++;
    pthread_mutex_unlock(&philos->meal_lock);

    pthread_mutex_unlock(philos->l_fork);
    pthread_mutex_unlock(philos->r_fork);
}

int	check_die(t_philo *philos, t_params *params)
{
	size_t	time_since_last_meal;

	pthread_mutex_lock(&philos->meal_lock);
	time_since_last_meal = get_current_time() - philos->last_meal_time ;
	pthread_mutex_unlock(&philos->meal_lock);

   // printf("Philosopher %d: Time since last meal: %zu,\n",
          // philos->id, time_since_last_meal);
	return (time_since_last_meal >= (params->time_until_die + 1));
}



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
            
			// **Check if a philosopher has died**
			if (check_die(&philos[i], params))
			{
                printf("Philosopher %d died while holding fork? %d\n", philos[i].id, philos[i].is_holding_fork);
				die(&philos[i]);
				simulation_running = 0;
				return (1);  // Stop simulation immediately
			}

			// **Check if philosopher has finished eating**
			pthread_mutex_lock(&philos[i].meal_lock);
			if (params->total_num_need_eats != -1 && philos[i].meals_eaten >= params->total_num_need_eats)
			{
				if (!philos[i].is_finished) // Only count once
				{
					philos[i].is_finished = 1;
					finished_philos++;
				}
			}
			pthread_mutex_unlock(&philos[i].meal_lock);
		}

		// **Stop when all philosophers have finished eating**
		if (params->total_num_need_eats != -1 && finished_philos == params->total_philos)
		{
			simulation_running = 0;
			return (0);
		}

		usleep(5000); // Small delay to reduce CPU usage
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
		{
			die(philos);
			return (NULL);  
		}
		eat(philos, params);
        if (check_die(philos, params) == 1)
		{
			die(philos);
			return (NULL);  
		}
		philo_sleep(philos, params);
        if (check_die(philos, params) == 1)
		{
			die(philos);
			return (NULL);
		}
		think(philos);
		meals_eaten++;
        if (params->total_num_need_eats != -1 && meals_eaten >= params->total_num_need_eats)
		{
			break ;
		}
		
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

	// **Monitor Simulation**
	if (params.total_num_need_eats == -1)
	{
		// **No meal limit → Stop when a philosopher dies**
		if (monitor_die(philos, &params))
			return (0);
	}
	else
	{
		// **Meal limit given → Stop when all philosophers finish eating**
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

	// **Destroy Mutexes**
	for (int i = 0; i < total_philos; i++)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].meal_lock);
	}

	// **Print philosopher meal counts**
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

There might be a race condition between updating the last_meal_time and checking for death. If the check_die function runs just after the philosopher picks up the forks but before they update their last_meal_time,
 it could incorrectly determine that the philosopher has starved.
*/
