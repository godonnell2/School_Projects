
#include "philo.h"

void	think( t_philo *philos)
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
		    usleep(5000);
        }

}

/*
Even though each philosopher follows a strict eat → sleep → think cycle, 
they are running in parallel on separate threads.
 Without proper synchronization, multiple philosophers could:
 Modify meals_eaten at the same time, causing race conditions.
Read/write last_meal_time while another philosopher (or a monitor thread)
 is checking it, leading to inconsistencies.
Since usleep() expects microseconds, we need to convert
 milliseconds to microseconds by multiplying by 1000.
 no and needed for locking because the forks are already ptrs
  // Avoid deadlock: Odd philosophers pick right fork first!!!!!
  otherwise everyone grabs left fork and prog stalls
  
*/

void die(t_philo *philos)
{
    size_t	time_ms;
	time_ms = get_current_time();
    philos->is_dead = 1;
	printf("%zu %d died\n", time_ms, philos->id);
}

void	eat(t_philo *philos, t_params *params)
{
    size_t start_time_ms = get_current_time();
      if (params->total_philos == 1)
    {
        pthread_mutex_lock(philos->l_fork);
        printf("%zu %d has taken a fork\n", start_time_ms, philos->id);
        
        // Wait until they die
        usleep(params->time_until_die * 1000);
        
        // Unlock the fork before dying
        pthread_mutex_unlock(philos->l_fork);
        
        die(philos);
        return;
    }

     if (philos->id % 2 == 0)
    {
        pthread_mutex_lock(philos->r_fork);
        printf("%zu %d has taken a fork\n", start_time_ms, philos->id);
        pthread_mutex_lock(philos->l_fork);
        printf("%zu %d has taken a fork\n", start_time_ms, philos->id);
    }
    else
    {
        pthread_mutex_lock(philos->l_fork);
        printf("%zu %d has taken a fork\n", start_time_ms, philos->id);
        pthread_mutex_lock(philos->r_fork);
        printf("%zu %d has taken a fork\n", start_time_ms, philos->id);
    }
    philos->last_meal_time = get_current_time();
    // pthread_mutex_lock(philos->meal_lock);

    printf("%zu %d is eating\n", start_time_ms, philos->id);
    philos->meals_eaten++;
    usleep(params->duration_eating * 1000);
   // pthread_mutex_unlock(philos->meal_lock);
    pthread_mutex_unlock(philos->l_fork);
	pthread_mutex_unlock(philos->r_fork);
  
}



int check_die(t_philo *philos, t_params *params)
{
    
    if (get_current_time() - philos->last_meal_time >= params->time_until_die) 
    // && philo->eating == 0) ??? philo meal lock??
    {
        return 1;
    }   
    return 0;
}

int monitor_die(t_philo *philos, t_params *params)
{
     int i;

    i = 0;
    while (i < params->total_philos)
    {
        int is_dead = check_die(&philos[i], params);
        if(is_dead)
        {
            die(philos);
            return 1;
        }
        i++;
    }
    return 0;
}


void *routine(void *arg)
{
 t_philo *philos = (t_philo *)arg; // Cast the argument back to t_philo
    t_params *params = philos->params; // Get params from philos struct
    int meals_eaten = 0; 
    while (1) 
    { 
         if (check_die(philos, params) ==1) {
           die(philos);
            break;
        }
        eat(philos, params);
        philo_sleep(philos, params);
        think(philos);
        meals_eaten++; 
        
        
     if (meals_eaten >= params->total_num_need_eats)
    {
        break;
    }
    }
     return NULL;
}

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
		params->total_num_need_eats = 10000;
}

//so forks are their own resource kind like opening an fd they need to be initialised
//before you use assign them to the philos in init philos
   void init_forks(pthread_mutex_t *forks, int total_philos)
    {
        int i = 0;
        while(i < total_philos)
        {
        pthread_mutex_init(&forks[i], NULL); 
       // pthread_mutex_init(&philos[i].meal_lock, NULL); //NOT SURE I NEED THIS
        i++;
        }
    }
// right fork  - first philo shares fork with final filo (circular)
void	init_philos(t_philo *philos,  pthread_mutex_t *forks, t_params *params)
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
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % params->total_philos];
        philos[i].params = params;
		i++;
	}
}


// pthread_mutex_t is a data type that represents a mutex (mutual exclusion) object.
int	main(int ac, char **av)
{
	t_philo			philos[PHILOS_MAX];
	pthread_mutex_t	forks[PHILOS_MAX];
    t_params params; 
    
	// if you use OR it always evaluates to true whoops DUH
	if (ac != 5 && ac != 6)
	{
		write(2, "Incorrect number of arguments \n", 31);
		return (-2);
	}
	if (check_args(av) == 1)
		return (-3);
    init_params(&params, av);
     int total_philos = params.total_philos;
 init_forks(forks, total_philos);
	init_philos( philos, forks, &params);
   
   
for (int i = 0; i < total_philos; i++)
     pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
   
for (int i = 0; i < total_philos; i++)
    pthread_join(philos[i].thread, NULL);
for (int i = 0; i < total_philos; i++) {
    printf("Philosopher %d ate %d times.\n", philos[i].id, philos[i].meals_eaten);
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
