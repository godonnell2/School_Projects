/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:17:46 by gro-donn          #+#    #+#             */
/*   Updated: 2025/02/26 08:26:18 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *philos)
{
	printf("Philosopher %d died\n Time since last meal: %zu\n", philos->id,
		get_current_time() - philos->last_meal_time);
	printf("%zu %d died\n", get_current_time(), philos->id);
	philos->is_dead = 1;
}

int	check_die(t_philo *philos, t_params *params)
{
	size_t	time_since_last_meal;

	pthread_mutex_lock(&philos->meal_lock);
	time_since_last_meal = get_current_time() - philos->last_meal_time;
	pthread_mutex_unlock(&philos->meal_lock);
	return (time_since_last_meal >= (params->time_until_die +1));
}

void	check_philosopher_meals(t_philo *philo, int *finished_philos,
		t_params *params)
{
	pthread_mutex_lock(&philo->meal_lock);
	if (params->total_num_need_eats != -1
		&& philo->meals_eaten >= params->total_num_need_eats)
	{
		if (!philo->is_finished)
		{
			philo->is_finished = 1;
			(*finished_philos)++;
		}
	}
	pthread_mutex_unlock(&philo->meal_lock);
}

int	monitor_die(t_philo *philos, t_params *params)
{
	int	finished_philos;
	int	i;

	finished_philos = 0;
	i = 0;
	while (1)
	{
		while (i < params->total_philos)
		{
			if (check_die(&philos[i], params))
			{
				die(&philos[i]);
				return (-51);
			}
			check_philosopher_meals(&philos[i], &finished_philos, params);
			i++;
		}
		i = 0;
		if (params->total_num_need_eats != -1
			&& finished_philos == params->total_philos)
		{
			return (0);
		}
		usleep(1000);
	}
}
