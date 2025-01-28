/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 08:09:15 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/28 16:38:25 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <limits.h>

const char	*skip_whitespace(const char *buffer)
{
	while (*buffer == ' ' || *buffer == '\n')
		buffer++;
	return (buffer);
}


#include <stdio.h>
// if (endptr == str) {
        //return str;  // No valid number found, return original string
const char *parse_number(const char *str, float *value) {
   
    char *endptr;
    *value = strtof(str, &endptr);  
 
    if (endptr == str) {
        return str;  
    }

   
    str = endptr;


    str = skip_whitespace(str);


    return str;  
}

const char *parse_hex_color(const char *str, int *color)
{
    char *end_ptr;

    if (str[0] == '0' && str[1] == 'x')
        str += 2;
    
    *color = strtol(str, &end_ptr, 16);
    
    return end_ptr;
}

int is_hex_digit(char c)
{
    return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

int hex_to_int(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return 0;
}