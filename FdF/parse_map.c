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


long * read_map_into_array(t_map *map, char *buffer)
{
    int array_size = map->height * map->width;
   long * map_array = malloc(array_size * sizeof(long));
    int i = 0;
    char *tmp_buff = buffer;
    while(i < array_size)
    {
        map_array[i] =  atol(tmp_buff);
        
        while (*tmp_buff != '\n' && *tmp_buff != ' ')
        {
            tmp_buff++;
        }
        tmp_buff++;
        i++;
   
    }
       if (i < array_size) 
       {
        fprintf(stderr, "Warning: Expected %d elements, but read %d elements.\n", array_size, i);
     }
    return map_array;
    
}


#include <limits.h>

void find_min_max(long *array, int array_size, t_map *map) {
    if (array_size <= 0)
     {
     
        map->z_min = 0; 
        map->z_max = 0; 
        return;
    }

  
   map->z_min = array[0];
   map->z_max = array[0];

   int i = 1; 
   while (i < array_size)
    {
        if (array[i] < map->z_min) {
            map->z_min = array[i];
        }
        if (array[i] > map->z_max) {
            map->z_max = array[i];
        }
        i++;
    }
}

// read ints and skip newlines and spaces until EOF or all
//  (then check how many elements you were expecting)
//Convert 3d pts to 2dpts
// find the edges and the vertices
//find min and max FINISHED


