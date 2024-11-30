#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// char	*ft_strndup(const char *s, size_t n)
// {
// 	size_t	len;
// 	char	*dup;
// 	size_t	i;

// 	len = 0;
// 	while (s[len] && len < n)
// 	{
// 		len++;
// 	}
// 	dup = (char *)malloc(len + 1);
// 	if (!dup)
// 	{
// 		return (NULL);
// 	}
// 	i = 0;
// 	while (i < len)
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[len] = '\0';
// 	return (dup);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	char	chr;
// 	char	*str;
// 	int		len;

// 	str = (char *)s;
// 	chr = (char)c;
// 	len = ft_strlen(str);
// 	if (chr == '\0')
// 		return (str + len);
// 	while (*str)
// 	{
// 		if (chr == *str)
// 		{
// 			return (str);
// 		}
// 		str++;
// 	}
// 	return (NULL);
// }



size_t ft_strlen_chr(char *str, char c) {
    size_t length = 0; // Initialize length counter

    if (!str) {
        return 0; // Return 0 if the string is NULL
    }
    // Count characters until the c is found
    while (str[length] && str[length] != c) {
        length++;
    }
    // If the c is a newline, include it in the count
    if (str[length] == '\n') {
        length++;
    }
    return length; // Return the length
}

char *str_join_buff(char *existingline, char *new_data) {
    char *joinedstring; // Pointer to hold the new joined string
    size_t existinglinelength = ft_strlen_chr(existingline, '\0'); // Length of the existing line
    size_t newdatalength = ft_strlen_chr(new_data, '\n'); // Length of the new data

    // Allocate memory for the new joined string
    joinedstring = malloc(existinglinelength + newdatalength + 1);
    if (!joinedstring) {
        free(existingline); // Free existing line if allocation fails
        return NULL;
    }
    joinedstring[existinglinelength + newdatalength] = '\0'; // Null-terminate the new string

    // Copy existing line into the new string
    for (size_t i = 0; i < existinglinelength; i++) {
        joinedstring[i] = existingline[i];
    }
    // Copy new data into the new string
    for (size_t j = 0; j < newdatalength; j++) {
        joinedstring[existinglinelength + j] = new_data[j];
    }

    free(existingline); // Free the old line
    // Shift remaining data in new_data to the start of the buffer
    size_t i = 0;
    while (new_data[newdatalength + i]) {
        new_data[i] = new_data[newdatalength + i];
        i++;
    }
    new_data[i] = '\0'; // Null-terminate the new data buffer

    return joinedstring; // Return the new joined string
}