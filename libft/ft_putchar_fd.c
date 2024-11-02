#include "libft.h"
#include <unistd.h> 

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}


/*  
choose if we want the to use a file descriptor obtained from the open
 system call, or we use 0, 1, or 2, to refer to the 0= standard input
 (ask user), 1=standard output, or 2=standard error can go to a file and save
 general vs error output 
 */

/*
void test_ft_putchar_fd() {

    const char *temp_filename = "test_output.txt";
    int fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
   
    if (fd == -1) {
        perror("Failed to open file");
        return;
    }

    char test_char = 'A';
    ft_putchar_fd(test_char, fd);

    close(fd);

    
    fd = open(temp_filename, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file for reading");
        return;
    }

    char read_char;
    ssize_t bytes_read = read(fd, &read_char, 1);
    read_char = (bytes_read == 1) ? read_char : '\0';

   
    close(fd);
    remove(temp_filename);

   
    assert(read_char == test_char);
    printf("Test passed: written character '%c' matches read character '%c'.\n", test_char, read_char);
}

int main() {
    test_ft_putchar_fd();
    return 0;
}
*/