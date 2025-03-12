/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:17:46 by gro-donn          #+#    #+#             */
/*   Updated: 2025/03/12 10:07:13 by gro-donn         ###   ########.fr       */
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

void	check_meal_count(t_philo *philo, int *finished_philos, t_params *params)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (params->num_eats != -1 && philo->meals_eaten >= params->num_eats)
		(*finished_philos)++;
	pthread_mutex_unlock(&philo->meal_lock);
}

int	check_philosopher_status(t_philo *philo, t_params *params,
		int *finished_philos)
{
	if (check_die(philo, params))
	{
		die(philo);
		return (-1);
	}
	check_meal_count(philo, finished_philos, params);
	return (0);
}

//  return (-1) A philosopher died
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
			if (check_philosopher_status(&philos[i], params,
					&finished_philos) == -1)
			{
				return (-1);
			}
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