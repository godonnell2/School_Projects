/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:02:20 by gro-donn          #+#    #+#             */
/*   Updated: 2025/02/21 08:58:29 by gro-donn         ###   ########.fr       */
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

void	die(t_philo *philos)
{
	size_t	time_ms;

	time_ms = get_current_time();
	philos->is_dead = 1;
	printf("%zu %d died\n", time_ms, philos->id);
}

//all odd philos have a tiny eat at the beginning 
void	eat(t_philo *philos, t_params *params)
{
	size_t	start_time_ms;

	start_time_ms = get_current_time();
	if (params->total_philos == 1)
	{
		pthread_mutex_lock(philos->l_fork);
        
		printf("%zu %d has taken a fork\n", start_time_ms, philos->id);
		// Wait until they die
		usleep(params->time_until_die * 1000);
		// Unlock the fork before dying
		pthread_mutex_unlock(philos->l_fork);
		die(philos);
		return ;
	}

    	pthread_mutex_lock(&philos->meal_lock);
	philos->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philos->meal_lock); // OMG moving the unlock up here made the difference between life and death
    // so that the monitor thread doesn’t think the philosopher is starving.
 
	if (philos->id % 2 == 1)
	{
        size_t lock_start_time_ms = get_current_time();
		pthread_mutex_lock(philos->r_fork);
         philos->is_holding_fork= 1;
		printf("%zu %d has taken a fork\n", lock_start_time_ms, philos->id);
         size_t wait_time = get_current_time() - lock_start_time_ms;
         printf("%zu %d waited %zu ms to take right fork\n", get_current_time(), philos->id, wait_time);
        usleep(10);  // Short delay before picking up the second fork think this made it worse
		
        lock_start_time_ms = get_current_time();
        pthread_mutex_lock(philos->l_fork);
        wait_time = get_current_time() - lock_start_time_ms;
        printf("%zu %d waited %zu ms to take left fork\n", get_current_time(), philos->id, wait_time);
		printf("%zu %d has taken a fork\n", start_time_ms, philos->id);
	}
	else
	{
       
          size_t lock_start_time_ms = get_current_time();
		pthread_mutex_lock(philos->l_fork);
        philos->is_holding_fork= 1;
         size_t wait_time = get_current_time() - lock_start_time_ms;
		printf("%zu %d has taken a fork\n", start_time_ms, philos->id);
          printf("%zu %d waited %zu ms to take left fork\n", get_current_time(), philos->id, wait_time);
          
        usleep(100);  // Short delay before picking up the second fork
        lock_start_time_ms = get_current_time();
		pthread_mutex_lock(philos->r_fork);
		printf("%zu %d has taken a fork\n", start_time_ms, philos->id);
         wait_time = get_current_time() - lock_start_time_ms;
          printf("%zu %d waited %zu ms to take right fork\n", get_current_time(), philos->id, wait_time);
	}

    size_t time_since_last_meal = get_current_time() - philos->last_meal_time;
    if (time_since_last_meal > params->time_until_die / 2 && time_since_last_meal < params->time_until_die - 200)
// If a philosopher is very behind, let them eat first
//If a philosopher hasn’t eaten for a long time, they will skip the delay and grab forks immediately.
//If they recently ate, they will pause for 250 microseconds, allowing a starving philosopher to grab the forks first.
//but onlydo it on philos who are not in immediate danger of dyring
    usleep(250);   
	printf("%zu %d is eating\n", start_time_ms, philos->id);
	philos->meals_eaten++;
	usleep(params->duration_eating * 1000);

	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
}

int	check_die(t_philo *philos, t_params *params)
{
	size_t	time_since_last_meal;

	pthread_mutex_lock(&philos->meal_lock);
	time_since_last_meal = get_current_time() - philos->last_meal_time;
	pthread_mutex_unlock(&philos->meal_lock);

   // printf("Philosopher %d: Time since last meal: %zu,\n",
          // philos->id, time_since_last_meal);
	return (time_since_last_meal >= params->time_until_die);
}



int	monitor_die(t_philo *philos, t_params *params)
{
	int	finished_philos;
	int	simulation_running;

	finished_philos = 0;
	simulation_running = 1;
	while (simulation_running) 
	{
		finished_philos = 0;
		for (int i = 0; i < params->total_philos; i++)
		{
			if (check_die(&philos[i], params))
			{
                if (philos[i].is_holding_fork)
                {
                 // Let them finish their turn if they are already eating
                continue;
                }
				die(&philos[i]); 
				return (1);        
			}
            
			if (philos[i].meals_eaten >= params->total_num_need_eats)
				finished_philos++;
           
		}
		if (finished_philos == params->total_philos)
		{
			simulation_running = 0;
			return (0);
		}
		usleep(200); // Small sleep to avoid CPU overuse was 100 
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
			break ;
		}
		eat(philos, params);
		philo_sleep(philos, params);
		think(philos);
		meals_eaten++;
		if (meals_eaten >= params->total_num_need_eats)
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
  
	if (monitor_die(philos, &params))
	{
		// If a philosopher dies, stop everything
		return (0);
	}
	for (int i = 0; i < total_philos; i++)
		pthread_join(philos[i].thread, NULL);
	
	for (int i = 0; i < total_philos; i++)
	{
		pthread_mutex_destroy(&forks[i]);
		pthread_mutex_destroy(&philos[i].meal_lock);
	}
      for (int i = 0; i < total_philos; i++)
	{
		printf("Philosopher %d ate %d times.\n", philos[i].id,
			philos[i].meals_eaten);
	}
	return (0);
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


*/
