#include "philo.h"

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
size_t get_current_time(void) {
    struct timeval time_now; 

    if (gettimeofday(&time_now, NULL) == -1) {
        write(2, "failure gettimeofday()\n", 24); 
        //SHOULD I RETURN???
    }

    return (time_now.tv_sec * 1000 + time_now.tv_usec / 1000);
}


  //need to delete this is just for testing
void print_human_readable_time(size_t milliseconds) {
    // Convert milliseconds to seconds
    time_t seconds = milliseconds / 1000;
    
    // Convert to struct tm
    struct tm *tm_info = localtime(&seconds);
    
    // Print the time in a human-readable format
    char buffer[26];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    printf("Human-readable time: %s\n", buffer);
}
