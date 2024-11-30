#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// if there is data we check to see if there's data in the store
// we look for first newline strchr DONE!! 
//as long as theres data in store have to clear it
// if we find a new line DONE!!
// we append up until and including newline to line strjoin DONE!!
// we use memmove to move from beyond newline to the back of the store DONE!!
// return the line DONE
// else append all of the store to line strjoin
// else we read into the store DONE!!!


static char *extract_line_from_store(t_store *store, char *line)
{
    char *newline_pos = store->value;
    while (*newline_pos && *newline_pos != '\n')
        newline_pos++;
    if (*newline_pos == '\n')
    {
        size_t line_length = newline_pos - store->value + 1;
        char *cpy = ft_strndup(store->value, line_length);
        if (!cpy)
        {
            free(line);
            return NULL;
        }
        char *temp = ft_strjoin(line, cpy);
        free(cpy);
        free(line);
        if (!temp)
            return NULL;
        line = temp;
        size_t remaining_bytes = store->bytes_stored - line_length;
        ft_memmove(store->value, store->value + line_length, remaining_bytes);
        store->bytes_stored = remaining_bytes;
        store->value[store->bytes_stored] = '\0';
        return line;
    }
    return NULL;
}

static char *append_store_to_line(t_store *store, char *line)
{
    char *temp = ft_strjoin(line, store->value);
    free(line);
    if (!temp)
        return NULL;
    line = temp;
    store->bytes_stored = 0;
    store->value[0] = '\0';
    return line;
}

static int read_into_store(int fd, t_store *store)
{
    int bytes_read = read(fd, store->value + store->bytes_stored, BUFFER_SIZE);
    if (bytes_read > 0)
    {
        store->bytes_stored += bytes_read;
        store->value[store->bytes_stored] = '\0';
    }
    return bytes_read;
}

static char *handle_end_of_file(t_store *store, char *line, int bytes_read)
{
      if (bytes_read == -1) 
     {
            free(line);
            store->bytes_stored = 0; 
            store->value[0] = '\0'; 
            return NULL;
        }
    if (line)
    {
        char *temp = ft_strjoin(line, store->value);
        free(line);
        if (!temp)
            return NULL;
        line = temp;
        store->bytes_stored = 0;
        store->value[0] = '\0';
    }
    return line;
}

char *get_next_line(int fd)
{
    static t_store store;
    char *line = NULL;

    if (fd < 0)
        return NULL;
    while (1)
    {
        if (store.bytes_stored > 0)
        {
            char *result = extract_line_from_store(&store, line);
            if (result)
                return result;
            line = append_store_to_line(&store, line);
            if (!line)
                return NULL;
        }
        int bytes_read = read_into_store(fd, &store);
        if (bytes_read <= 0)
            return handle_end_of_file(&store, line, bytes_read);
    }
}