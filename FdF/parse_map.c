#include "fdf.h"
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024 

void handle_error(const char *message)
{
    printf("%s\n", message);
	exit (1);
}

//READ THE WHOLE FILE INTO A STRING(BUFFER)
 //DETERMINE WIDTH AND HEIGHT
 //LOOK FOR NEW LINE  = height
 //LOOK FOR WIDTH COUNT WORDS and check they are the same otherwise throw error 
// record height of any non empty lines until EOF ie GNL=0

//NESTED LOOP
//FILL WIDTH 
//FILL HEIGHT 
////store MIN MAX 
char *read_file_to_buffer(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        handle_error("Failed to open file");

    char *buffer = malloc(BUFFER_SIZE +1);
    if (!buffer)
    {
        close(fd);
        handle_error("Memory allocation error");
    }

    int total_bytes_read = 0;
    int bytes_read;

    while ((bytes_read = read(fd, buffer + total_bytes_read, BUFFER_SIZE)) > 0)
    {
        total_bytes_read += bytes_read;

        if (total_bytes_read + BUFFER_SIZE > total_bytes_read)
        {
            char *new_buffer = malloc(total_bytes_read + BUFFER_SIZE + 1);
            if (!new_buffer)
            {
                free(buffer);
                close(fd);
                handle_error("Memory allocation error");
            }
            memcpy(new_buffer, buffer, total_bytes_read);
            free(buffer);
            buffer = new_buffer;
        }
    }

    if (bytes_read == -1)
    {
        free(buffer);
        close(fd);
        handle_error("Error reading file");
    }

    buffer[total_bytes_read] = '\0';
    close(fd);
    return buffer;
}


static int count_words(const char *line)
{
    int count = 0;
    int in_word = 0;

    while (*line && *line != '\n')
    {
        if (*line != ' ' && !in_word)
        {
            count++;
            in_word = 1;
        }
        else if (*line == ' ')
        {
            in_word = 0;
        }
        line++;
    }

    return count;
}

void determine_dimensions(const char *buffer, t_map *map)
{
    int height = 0;
    int width = 0;
    int first_line = 1;

    while (*buffer)
    {
        const char *line_start = buffer;

        while (*buffer && *buffer != '\n')
        {
            buffer++;
        }
      
        if (buffer > line_start) 
        {
            int current_width = count_words(line_start);

            if (first_line)
            {
                
                width = current_width;
                first_line = 0;
            }
            else if (current_width != width)
            {
                handle_error("Error: inconsistent width in map data");
            }
            
        }

        if (*buffer == '\n')
        {
            buffer++;
            height++;
        }
    }
    map->height = height;
    map->width = width;
}






