/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:17:46 by gro-donn          #+#    #+#             */
/*   Updated: 2025/02/26 19:45:50 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philos)
{
	pthread_mutex_lock(&philos->params->sim_lock);
	if (philos->params->simulation_running)
	{
		printf("%zu %d died\n", get_current_time() - philos->start_time,
			philos->id);
		philos->params->simulation_running = 0;
	}
	pthread_mutex_unlock(&philos->params->sim_lock);
}

int	check_die(t_philo *philos, t_params *params)
{
	size_t	time_since_last_meal;

	pthread_mutex_lock(&philos->meal_lock);
	time_since_last_meal = get_current_time() - philos->last_meal_time;
	pthread_mutex_unlock(&philos->meal_lock);
	return (time_since_last_meal >= params->time_until_die);
}

int	monitor_die(t_philo *philos, t_params *params)
{
	int	finished_philos;
	int	i;

	while (1)
	{
		finished_philos = 0;
		i = 0;
		while (i < params->total_philos)
		{
			if (check_die(&philos[i], params))
			{
				die(&philos[i]);
				return (-1);
			}
			pthread_mutex_lock(&philos[i].meal_lock);
			if (params->num_eats != -1
				&& philos[i].meals_eaten >= params->num_eats)
			{
				finished_philos++;
			}
			pthread_mutex_unlock(&philos[i].meal_lock);
			i++;
		}
		if (params->num_eats != -1 && finished_philos == params->total_philos)
		{
			pthread_mutex_lock(&params->sim_lock);
			params->simulation_running = 0;
			pthread_mutex_unlock(&params->sim_lock);
			return (0);
		}
		usleep(1000);
	}
}

// usleep(1000); // Monitor frequency - check every 1ms