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
 //LOOK FOR NEW LINE  = rows
 //LOOK FOR WIDTH COUNT WORDS and check they are the same otherwise throw error 
// record rows of any non empty lines until EOF ie GNL=0

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
    int rows = 0; //DOBLE CHECK THIS OFF BY ONE?
    int cols = 0;
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
                
                cols = current_width;
                first_line = 0;
            }
            else if (current_width != cols)
            {
                handle_error("Error: inconsistent cols in map data");
            }
            
        }

        if (*buffer == '\n')
        {
            buffer++;
            rows++;
        }
    }
    map->rows = rows;
    map->cols = cols;
}


long * read_map_into_array(t_map *map, char *buffer)
{
    int array_size = map->rows * map->cols;
   long * map_array = malloc(array_size * sizeof(long));
    int i = 0;
    char *tmp_buff = buffer;
    while(i < array_size)
    {
     // Skip any leading whitespace
        while (*tmp_buff == ' ' || *tmp_buff == '\n') {
            tmp_buff++;
        }

        // Check for end of buffer
        if (*tmp_buff == '\0') {
            break; // Exit if we reach the end of the buffer
        }

        // Read the number
        map_array[i] = atol(tmp_buff);


        // Move the pointer to the end of the number
        while (*tmp_buff != ' ' && *tmp_buff != '\n' && *tmp_buff != '\0') {
            tmp_buff++;
        }
        
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


void generate_3d_points(t_map *map, long *map_array, t_point3d *points) 
{
    int index = 0;
    int y = 0; 
    while (y < map->rows) {
        int x = 0; 
        while (x < map->cols) 
        {
            points[index].x = x; 
            points[index].y = y; 
            points[index].z = map_array[y * map->cols + x]; 
            index++; 
            x++; 
        }
        y++; 
    }
}

// so basically this is how we drop the z axis 
// because screens dont have a z axis

void convert_to_isometric(t_map *map, t_point3d *points, t_point2d *iso_points)
{
    for (int i = 0; i < map->rows * map->cols; i++)
    {
        // Retrieve the 3D coordinates from the points array
        float x = points[i].x;
        float y = points[i].y;
        float z = points[i].z;

        // Apply the isometric projection formula
        float iso_x = (x - y) * cos(0.523599); // 0.523599 radians = 30 degrees
        float iso_y = (x + y) * sin(0.523599) - z;

        // Store the resulting 2D point in the iso_points array
        iso_points[i].x = iso_x;
        iso_points[i].y = iso_y;
    }
}

	void scale_and_offset_points(t_point2d *iso_points, t_map *map, int window_width, int window_height)
{
    int total_points = map->cols * map->rows;
    int offset_x = window_width / 2;   // Center horizontally
    int offset_y = window_height / 2; // Center vertically

    for (int i = 0; i < total_points; i++)
    {
        iso_points[i].x *= SCALE_FACTOR; // Apply scaling
        iso_points[i].y *= SCALE_FACTOR; // Apply scaling
        iso_points[i].x += offset_x;     // Center on screen
        iso_points[i].y += offset_y;     // Center on screen
    }
}

	// t_edge edges[] = {
	// 	{.start = 0, .end = 1},
	// 	{.start = 1, .end = 3},
	// 	{.start = 3, .end = 2},
	// 	{.start = 2, .end = 0},
	// }; 

    // NEED TO POPULATE SOMETHING LIKE THIS FN
void populate_edges(t_map *map, t_edge **edges, int *edges_count)
{
    int cols = map->cols;
    int rows = map->rows;
    int total_edges = (cols - 1) * rows + (rows - 1) * cols;

    *edges = malloc(total_edges * sizeof(t_edge));
    if (edges == NULL) {
        fprintf(stderr, "Memory allocation failed for edges.\n");
        exit(EXIT_FAILURE);
    }
   
    *edges_count = 0;

    for (int y = 0; y < rows; y++) 
    {
        for (int x = 0; x < cols; x++)
        {
            int current_index = y * cols+ x;

            // Connect to the right neighbor
            if (x < cols - 1) {
                (*edges)[*edges_count].start = current_index;
                (*edges)[*edges_count].end = current_index + 1;
                (*edges_count)++;
            }

            // Connect to the bottom neighbor
            if (y < rows - 1) {
                (*edges)[*edges_count].start = current_index;
                (*edges)[*edges_count].end = current_index + cols;
                (*edges_count)++;
            }
        }
    }

}
// read ints and skip newlines and spaces until EOF or all
//  (then check how many elements you were expecting)
//Convert 3d pts to 2dpts
// find the edges and the vertices
//find min and max FINISHED like the square printing
//calc x,y so that i have 3d pts(x, y,z ) 
//calculate the edges only dependent on the cols and the rows
// the edges are just teh grid
// scale min max

// The grid edges will form the structure, and the z values will create the
//  "rows" variations that make the grid look like a 3D terrain in 
//  isometric projection.