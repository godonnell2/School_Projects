#include "libft.h" 

int	ft_atoi(char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	
	 while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
           str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if(str[i] == '-' || str[i] == '+')
	{
		if(str[i] == '-')
			neg *= -1;
		i++;
	}
	
	while(str[i] >= '0' && str[i] <='9')
	{
	res =(str[i] -'0') + (res * 10);
	i++;
	}
	return res *neg;
}
