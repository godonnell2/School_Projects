/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:23:29 by gro-donn          #+#    #+#             */
/*   Updated: 2025/02/26 19:49:42 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philos)
{
	pthread_mutex_lock(&philos->params->sim_lock);
	if (philos->params->simulation_running)
		printf("%zu %d is thinking\n", get_current_time() - philos->start_time,
			philos->id);
	pthread_mutex_unlock(&philos->params->sim_lock);
}

/*
it reduces CPU usage
*/
void	philo_sleep(t_philo *philos, t_params *params)
{
	size_t	start_time_ms;

	start_time_ms = get_current_time();
	pthread_mutex_lock(&params->sim_lock);
	if (params->simulation_running)
		printf("%zu %d is sleeping\n", start_time_ms - philos->start_time,
			philos->id);
	pthread_mutex_unlock(&params->sim_lock);
	while (get_current_time() - start_time_ms < params->duration_sleeping)
	{
		pthread_mutex_lock(&params->sim_lock);
		if (!params->simulation_running)
		{
			pthread_mutex_unlock(&params->sim_lock);
			return ;
		}
		pthread_mutex_unlock(&params->sim_lock);
		usleep(500);
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
Delay before second fork: Allows slight desynchronization to avoid two adjacent
 philosophers competing at the exact same time.
✅ Immediate last_meal_time update: Ensures the death check mechanism doesn't
 falsely detect starvation due to a delayed update.
*/
// all odd philos have a tiny eat at the beginning

// Small delay for odd philosophers to reduce contention
void	eat(t_philo *philos, t_params *params)
{
	size_t	start_eating;

	pthread_mutex_lock(&params->sim_lock);
	if (!params->simulation_running)
	{
		pthread_mutex_unlock(&params->sim_lock);
		return ;
	}
	pthread_mutex_unlock(&params->sim_lock);
	if (params->total_philos == 1)
	{
		pthread_mutex_lock(philos->r_fork);
		pthread_mutex_lock(&params->sim_lock);
		if (params->simulation_running)
			printf("%zu %d has taken a fork\n", get_current_time()
				- philos->start_time, philos->id);
		pthread_mutex_unlock(&params->sim_lock);
		usleep(params->time_until_die * 1000);
		pthread_mutex_unlock(philos->r_fork);
		return ;
	}
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->l_fork);
		pthread_mutex_lock(philos->r_fork);
	}
	else
	{
		usleep(500);
		pthread_mutex_lock(philos->r_fork);
		pthread_mutex_lock(philos->l_fork);
	}
	pthread_mutex_lock(&params->sim_lock);
	if (params->simulation_running)
	{
		printf("%zu %d has taken a fork\n", get_current_time()
			- philos->start_time, philos->id);
		printf("%zu %d has taken a fork\n", get_current_time()
			- philos->start_time, philos->id);
	}
	pthread_mutex_unlock(&params->sim_lock);
	pthread_mutex_lock(&philos->meal_lock);
	philos->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philos->meal_lock);
	pthread_mutex_lock(&params->sim_lock);
	if (params->simulation_running)
		printf("%zu %d is eating\n", get_current_time() - philos->start_time,
			philos->id);
	pthread_mutex_unlock(&params->sim_lock);
	start_eating = get_current_time();
	while (get_current_time() - start_eating < params->duration_eating)
	{
		pthread_mutex_lock(&params->sim_lock);
		if (!params->simulation_running)
		{
			pthread_mutex_unlock(&params->sim_lock);
			break ;
		}
		pthread_mutex_unlock(&params->sim_lock);
		usleep(500);
	}
	pthread_mutex_lock(&philos->meal_lock);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->meal_lock);
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
}

// Cast the argument back to t_philo
// Get params from philos struct
void	*routine(void *arg)
{
	t_philo		*philos;
	t_params	*params;

	int should_continue ;
	philos = (t_philo *)arg;
	params = philos->params;
	while (1)
	{
		pthread_mutex_lock(&params->sim_lock);
		should_continue = params->simulation_running;
		pthread_mutex_unlock(&params->sim_lock);
		if (!should_continue)
			break ;
		eat(philos, params);
		philo_sleep(philos, params);
		think(philos);
		pthread_mutex_lock(&philos->meal_lock);
		if (params->num_eats != -1 && philos->meals_eaten >= params->num_eats)
		{
			philos->is_finished = 1;
			pthread_mutex_unlock(&philos->meal_lock);
			break ;
		}
		pthread_mutex_unlock(&philos->meal_lock);
		usleep(100);
	}
	return (NULL);
}
// usleep(100);
// Small delay to prevent CPU hogging (that small delay that will
// make the even and odd philos work together)