#include "fdf.h"

#define BUFFER_SIZE 1024 

void handle_error(const char *message)
{
    ft_printf("%s\n", message);
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
static char *read_file_to_buffer(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
        handle_error("Failed to open file", 1);

    char *buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
    {
        close(fd);
        handle_error("Memory allocation error", 1);
    }

    size_t total_bytes_read = 0;
    size_t bytes_read;

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
                handle_error("Memory allocation error", 1);
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
        handle_error("Error reading file", 1);
    }

    buffer[total_bytes_read] = '\0';
    close(fd);
    return buffer;
}

static int count_words(const char *line)
{
    int count = 0;
    int in_word = 0;

    while (*line)
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

static void determine_dimensions(const char *buffer, t_map *map)
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

            height++;
        }

        if (*buffer == '\n')
        {
            buffer++;
        }
    }
    map->height = height;
    map->width = width;
}

static void allocate_map_array(t_map *map)
{
    int ***array;
    int **rows;
    int *cells;
    size_t total_cells = map->height * map->width * 2; // Each cell holds 2 integers

    // Allocate memory for rows and cells in a single block
    cells = malloc(total_cells * sizeof(int));
    rows = malloc(map->height * sizeof(int *));
    array = malloc(map->height * sizeof(int **));

    if (!array || !rows || !cells)
        handle_error("Memory allocation error for map");

    // Link rows to the cells
    for (int row = 0; row < map->height; row++)
    {
        rows[row] = &cells[row * map->width * 2];
        array[row] = malloc(map->width * sizeof(int *));
        if (!array[row])
            handle_error("Memory allocation error for map row");

        for (int col = 0; col < map->width; col++)
        {
            array[row][col] = &rows[row][col * 2];
        }
    }

    map->array = array; // Assign the array to the map structure
}

 void free_map(t_map *map)
{
    if (map->array)
    {
        free(map->array[0][0]); // Free the cells
        free(map->array[0]);    // Free the row pointers
        free(map->array);       // Free the array of pointers
    }
}

static void find_min_max(t_map *map, int i, int j, int *z_max)
{
    static int z_min; // Static variable to hold the minimum value

    if (i == 0 && j == 0) // Initialize z_min on the first call
        z_min = map->array[0][0][0];

    if (i >= map->height) // Base case: if we have processed all rows
        return;

    if (j >= map->width) // Move to the next row
    {
        find_min_max(map, i + 1, 0, z_max);
        return;
    }

    if (map->array[i][j][0] < z_min)
        z_min = map->array[i][j][0];
    if (map->array[i][j][0] > *z_max)
        *z_max = map->array[i][j][0];

    find_min_max(map, i, j + 1, z_max); // Move to the next column

    if (i == map->height - 1 && j == map->width - 1) // On the last call, set the final min value
    {
        map->z_min = z_min;
    }
}

static void ft_get_z_min_max(t_map *map)
{
    int z_max = map->array[0][0][0]; // Initialize z_max to the first element
    find_min_max(map, 0, 0, &z_max);
    map->z_max = z_max; // Set the maximum value in the map structure
}