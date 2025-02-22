/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:26:10 by gro-donn          #+#    #+#             */
/*   Updated: 2024/11/29 14:41:07 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#if BUFFER_SIZE < 1
#error BUFFER_SIZE has to be > 0
#endif
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct t_store
{
    size_t capacity;
    char value[BUFFER_SIZE + 1];
} t_store;

char *get_next_line(int fd);
void *free_store_value(t_store *store);
char *get_next_line_store(int fd, t_store *store);

#endif
