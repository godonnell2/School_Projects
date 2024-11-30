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


char *get_next_line(int fd) {
    static char buffer[BUFFER_SIZE + 1]; // Buffer to hold read data
    int bytes_read; // Number of bytes read from the file descriptor
    char *line = NULL; // Pointer to hold the line to be returned

    bytes_read = 1; // Initialize bytes_read to enter the loop
    while ((fd >= 0 ) && bytes_read > 0) {
        if (buffer[0]!='\0') { // If there is data in the buffer
            line = str_join_buff(line, buffer); // Join the current line with the buffer
            if (!line) {
                return NULL; // Return NULL if memory allocation fails
            }
            // Check if the last character in the line is a newline
            if (line[ft_strlen_chr(line, '\n') - 1] == '\n') {
                break; // Exit the loop if a newline is found
            }
        } else { // If the buffer is empty, read more data
            bytes_read = read(fd, buffer, BUFFER_SIZE); // Read from the file descriptor
            if (bytes_read < 0) {
                return free(line), NULL; // Return NULL on read error
            }
            buffer[bytes_read] = '\0'; // Null-terminate the buffer
        }
    }
    return line; // Return the constructed line
}