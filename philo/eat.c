/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 10:10:53 by gro-donn          #+#    #+#             */
/*   Updated: 2025/03/12 19:03:26 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Even though each philosopher follows a strict eat → sleep → think cycle,
they are running in parallel on separate threads. 
usleep() expects micros, CONVERT millis to micross by multiplying by 1000.
 no & needed for locking because the forks are already ptrs

AVOID DEADLOCK: Odd philosophers pick right fork first!!!!!
 all odd philos have a tiny  sleep at the beginning desynchronization 
  otherwise everyone grabs left fork and prog stalls
  
✅ Immediate last_meal_time update: Ensures the death check mechanism doesn't
 falsely detect starvation due to a delayed update.
 want to let the OS do as much as poss
*/


void	handle_single_philosopher(t_philo *philos, t_params *params)
{
	pthread_mutex_lock(philos->r_fork);
	if (safe_print(philos, "has taken a fork"))
		usleep(params->time_until_die * 1000);
	pthread_mutex_unlock(philos->r_fork);
}

void	take_forks(t_philo *philos)
{
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
	if (safe_print(philos, "has taken a fork"))
		safe_print(philos, "has taken a fork");
}

void	perform_eating(t_philo *philos, t_params *params)
{
	size_t	start_eating;

	pthread_mutex_lock(&philos->meal_lock);
	philos->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philos->meal_lock);
	if (!safe_print(philos, "is eating"))
		return ;
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
}

void	eat(t_philo *philos, t_params *params)
{
	pthread_mutex_lock(&params->sim_lock);
	if (!params->simulation_running)
	{
		pthread_mutex_unlock(&params->sim_lock);
		return ;
	}
	pthread_mutex_unlock(&params->sim_lock);
	if (params->total_philos == 1)
	{
		handle_single_philosopher(philos, params);
		return ;
	}
	take_forks(philos);
	perform_eating(philos, params);
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
}
