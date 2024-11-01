#include "libft.h"

char * ft_strjoin(char const *s1, char const *s2)
{
    // if (!s1 && !s2)
	// 	return (ft_strdup(""));
	// if (s1 && !s2)
	// 	return (ft_strdup(s1));
	// if (!s1 && s2)
	// 	return (ft_strdup(s2));

    size_t len_total = ft_strlen(s1) + ft_strlen(s2) + 1; 
    char * arr = (char *)malloc(len_total *sizeof(char));
    if(arr == NULL)
        return NULL;
    ft_bzero(arr, len_total);
    ft_strlcat(arr, s1, len_total);
    ft_strlcat(arr, s2, len_total);
    return arr;
}

int main()
{
    char const *s1 = NULL;
    char const *s2 = "grace";
    char * arr = ft_strjoin(s1, s2);
    printf("%s", arr);
    free(arr);
}