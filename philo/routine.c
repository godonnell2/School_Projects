#include "philo.h"

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
	// size_t	time_ms;
	// time_ms = get_current_time();
	printf("Philosopher %d died. Last meal time: %zu, Current time: %zu,
		Time since last meal: %zu\n", philos->id, philos->last_meal_time,
		get_current_time(), get_current_time() - philos->last_meal_time);
	printf("%zu %d died\n", get_current_time(), philos->id);
	philos->is_dead = 1;
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
void	eat(t_philo *philos, t_params *params)
{
	if (params->total_philos == 1)
	{
		usleep(params->time_until_die * 1000);
		die(philos);
		return ;
	}
	if (philos->id % 2 == 1)
	{
		pthread_mutex_lock(philos->r_fork);
		printf("%zu %d has taken a fork\n", get_current_time(), philos->id);
		pthread_mutex_lock(philos->l_fork);
		printf("%zu %d has taken a fork\n", get_current_time(), philos->id);
	}
	else
	{
		pthread_mutex_lock(philos->l_fork);
		printf("%zu %d has taken a fork\n", get_current_time(), philos->id);
		pthread_mutex_lock(philos->r_fork);
		printf("%zu %d has taken a fork\n", get_current_time(), philos->id);
	}
	pthread_mutex_lock(&philos->meal_lock);
	philos->last_meal_time = get_current_time();
	pthread_mutex_unlock(&philos->meal_lock);
	printf("%zu %d is eating\n", get_current_time(), philos->id);
	usleep(params->duration_eating * 1000);
	pthread_mutex_lock(&philos->meal_lock);
	philos->meals_eaten++;
	pthread_mutex_unlock(&philos->meal_lock);
	pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
}