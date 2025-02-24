/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:02:25 by gro-donn          #+#    #+#             */
/*   Updated: 2025/02/23 18:07:07 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *av)
{
	int	i;

	i = 0;
	while (av[i] != '\0')
	{
		if (av[i] < '0' || av[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(char **av)
{
	if (ft_atoi(av[1]) > PHILOS_MAX || ft_atoi(av[1]) <= 0
		|| is_digit(av[1]) == 0)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(av[2]) <= 0 || is_digit(av[2]) == 0)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(av[3]) <= 0 || is_digit(av[3]) == 0)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(av[4]) <= 0 || is_digit(av[4]) == 0)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || is_digit(av[5]) == 0))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

void	init_params(t_params *params, char **av)
{
	params->total_philos = ft_atoi(av[1]);
	params->time_until_die = ft_atoi(av[2]);
	params->duration_eating = ft_atoi(av[3]);
	params->duration_sleeping = ft_atoi(av[4]);
	if (av[5])
		params->total_num_need_eats = ft_atoi(av[5]);
	else
		params->total_num_need_eats = -1;
}

// so forks are their own resource kind like opening an fd they need to be initialised
// before you use assign them to the philos in init philos
void	init_forks_mutexes(pthread_mutex_t *forks, int total_philos,
		t_philo *philos)
{
	int	i;

	i = 0;
	while (i < total_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		pthread_mutex_init(&philos[i].meal_lock, NULL);
		i++;
	}
}
// right fork  - first philo shares fork with final filo (circular)
void	init_philos(t_philo *philos, pthread_mutex_t *forks, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->total_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].start_time = get_current_time();
		philos[i].last_meal_time = get_current_time();
		philos[i].is_dead = 0;
        philos[i].is_finished = 0;
        philos[i].is_holding_fork = 0;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % params->total_philos];
		philos[i].params = params;
		i++;
	}
}