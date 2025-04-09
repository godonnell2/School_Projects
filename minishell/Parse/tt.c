#include <stdio.h>
#include <stdlib.h>     // For getenv()
#include <term.h>       // For terminfo functions
#include <unistd.h>     // For tty functions

int main() {
    // Initialize terminal capabilities
    char term_buffer[2048];
    char *term_type = getenv("TERM");
    if (!term_type) {
        fprintf(stderr, "TERM environment variable not set\n");
        return 1;
    }

    if (tgetent(term_buffer, term_type) <= 0) {
        perror("tgetent");
        return 1;
    }

    // Get the clear screen capability (use "clear" instead of "cl" for better compatibility)
    char *clear_screen_cap = tigetstr("clear");
    if (clear_screen_cap == (char *)-1 || !clear_screen_cap) {
        fprintf(stderr, "Terminal does not support 'clear'\n");
        return 1;
    }

    // Clear the screen
    putp(clear_screen_cap);

    // Move the cursor to (10, 5)
    char *cursor_move = tigetstr("cup");
    if (cursor_move == (char *)-1 || !cursor_move) {
        fprintf(stderr, "Terminal does not support 'cup'\n");
        return 1;
    }
    char *cursor_pos = tgoto(cursor_move, 5, 5);
    putp(cursor_pos);

    printf("Hello, World!\n");
    return 0;
}
//gcc -o tt tt.c -lncurses 

/*
1. Checking and Identifying Terminals
int isatty(int fd);
Description:
Checks if the given file descriptor (fd) refers to a terminal device.
Useful for checking if a program's output is being piped to a file or displayed in a terminal.


char *ttyname(int fd);
Helps identify which terminal a process is running in.

int ttyslot(void);
Description:
Returns the index of the current terminal in the system’s terminal table


2. Controlling Terminal Attributes
4. Termcap (Terminal Capabilities) Functions
These functions help manage terminal capabilities and cursor movements. They are part of the Termcap librar
*/