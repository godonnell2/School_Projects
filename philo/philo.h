#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>   //gettimeofday

#define PHILOS_MAX 200

typedef struct s_params
{
     int	total_philos;
       int	total_num_need_eats;  
         size_t duration_eating; 
    size_t duration_sleeping;
        size_t time_until_die;
} t_params;

typedef struct s_philo 
{
    int id;
    int meals_eaten;
    size_t last_meal_time;
    size_t	start_time;  
    int	is_dead;
    pthread_t thread;
    pthread_mutex_t	*r_fork;   //these have to be ptrs to pthread mutex not values!
    // ! otherwise  This creates a separate mutex for each philosopher which would defeat the 
    // whole purpse
	pthread_mutex_t	*l_fork; 
     t_params *params; // pthread_create allows only one argument, add a t_params *params field in t_philo:
   // pthread_mutex_t *meal_lock;NOT SURE I NEED THIS
    //NEEDMORE ???
} t_philo;

int	ft_atoi(char *str);
size_t get_current_time(void);
void print_human_readable_time(size_t milliseconds);

#endif //PHILO_H