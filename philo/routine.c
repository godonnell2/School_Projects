/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:23:29 by gro-donn          #+#    #+#             */
/*   Updated: 2025/03/15 19:35:07 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philos)
{
	safe_print(philos, "is thinking");
}

/*
usleep delay reduces CPU usage
 repeatedly checking simulation_running with usleep
*/
void	philo_sleep(t_philo *philos, t_params *params)
{
	size_t	start_time_ms;
	int		running;

	start_time_ms = get_current_time();
	safe_print(philos, "is sleeping");
	while (get_current_time() - start_time_ms < params->duration_sleeping)
	{
		pthread_mutex_lock(&params->sim_lock);
		running = params->simulation_running;
		pthread_mutex_unlock(&params->sim_lock);
		if (!running)
			return ;
		usleep(100);
	}
}

// Cast the argument back to t_philo
// Get params from philos struct

void	check_meals(t_philo *philos, t_params *params)
{
	pthread_mutex_lock(&philos->meal_lock);
	if (params->num_eats != -1 && philos->meals_eaten >= params->num_eats)
	{
		philos->is_finished = 1;
	}
	pthread_mutex_unlock(&philos->meal_lock);
}

void	perform_philosopher_actions(t_philo *philos, t_params *params)
{
	if (philos->is_finished)
		return ;
	eat(philos, params);
	philo_sleep(philos, params);
	think(philos);
	check_meals(philos, params);
}

void	*routine(void *arg)
{
	t_philo		*philos;
	t_params	*params;
	int			running;

	philos = (t_philo *)arg;
	params = philos->params;
	while (1)
	{
		pthread_mutex_lock(&params->sim_lock);
		running = params->simulation_running;
		pthread_mutex_unlock(&params->sim_lock);
		if (!running)
			break ;
		perform_philosopher_actions(philos, params);
		usleep(100);
	}
	return (NULL);
}
// usleep(100);
// thefnprintf is a resource writing to term so have lock
// Small delay to prevent CPU hogging (that small delay that will
// make the even and odd philos work together)
// This function is the main execution loop for each philosopher thread.
//  Each philosopher runs this function independently in a separate thread.
// If the simulation is running, the philosopher performs its actions
//  (eating, sleeping, thinking).
// usleep(100); is a short delay to prevent busy-waiting, reducing CPU usage.
