/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:49:54 by gro-donn          #+#    #+#             */
/*   Updated: 2025/03/12 10:19:35 by gro-donn         ###   ########.fr       */
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

int	ft_atoi(char *str)
{
	unsigned long long	nb;
	int					sign;
	int					i;

	nb = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (sign * nb);
}

// Declare a variable of type struct timeval
// Calculate the current time in milliseconds
size_t	get_current_time(void)
{
	struct timeval	time_now;

	if (gettimeofday(&time_now, NULL) == -1)
	{
		write(2, "failure gettimeofday()\n", 24);
	}
	return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}

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

// NEED REVIEW
// It prevents race conditions when multiple philosophers
// try to print messages simultaneously.
// Ensures that checking simulation_running and printing are
// atomic (happen together safely)
// Prevents Printing After Simulation Ends
// Without this check, a philosopher might print after dying,
// which would be incorrect.
int	safe_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->params->sim_lock);
	if (philo->params->simulation_running)
	{
		printf("%zu %d %s\n", get_current_time() - philo->start_time, philo->id,
			msg);
		pthread_mutex_unlock(&philo->params->sim_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->params->sim_lock);
	return (0);
}
