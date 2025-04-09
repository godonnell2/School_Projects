#include "rl.h"

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
Command Tokenization
Split input into tokens (e.g., "ls -l" → ["ls", "-l", NULL]).
✅ Trim whitespace and tokenize the input into command + arguments (strtok() or strsep()).
📌 Example: shell      $ ls -l /home
📌 Output: css        ["ls", "-l", "/home"]
*/

int main() {
    char *input;

    while (1) {
        input = readline("> ");  // Read input from the user
        if (!input ) 
            break;       // Exit on EOF (Ctrl+D)
        if (*input == '\0')
            continue;
        if (*input) 
        {
            add_history(input);   // Add non-empty input to history
            printf("You entered: %s\n", input);
        }

        free(input);             // Free the allocated input buffer
    }

    clear_history();         // Clear history before exiting
    return 0;
}

/*
    int exec(t_node node)
    {
    if(node.type == |)
    return execpipe(node.l, node.r)
    else
    return execsimplecommand(node.value)
    }
*/

//gcc -o rl rl.c -lreadline 
// need to include -lreadline
// ctrl d == to exit


/*
pid_t wait(int *status);
Description:

Waits for any child process to change state (typically to exit).

Blocks execution until a child terminates.

Stores the exit status of the terminated child in status (if non-null).

Returns the PID of the terminated child.

Limitations:

Waits for any child process (cannot specify a particular one).

No options for non-blocking behavior.



pid_t waitpid(pid_t pid, int *status, int options);
Description:

Similar to wait(), but allows you to:

Wait for a specific child (pid > 0).

Wait for any child in a process group (pid < -1).

Wait for any child (pid == -1, same as wait()).

The options argument can modify behavior:

WNOHANG: Non-blocking mode (returns immediately if no child has exited).

WUNTRACED: Also returns if a child is stopped.

WCONTINUED: Also returns if a stopped child resumes.

Returns the PID of the terminated (or changed) child.

pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
Description:

A more powerful version of waitpid(), adding the struct rusage *rusage argument like wait3().

Allows waiting for:

A specific process (pid > 0).

Any child (pid == -1).

A process group (pid < -1).

Provides resource usage info about the child process.

WNOHANG: Non-blocking mode
Default behavior (without WNOHANG): waitpid() blocks execution until a child process changes state (e.g., terminates).

With WNOHANG: Instead of blocking, waitpid() immediately returns:

If a child has changed state (e.g., exited), it returns the child’s PID.

If no child has exited, it returns 0 instead of waiting.

If there are no child processes left, it returns -1 and sets errno to ECHILD.

🔹 Use case:
When you don’t want to block the parent process and instead want to check periodically if a child has exited.

WUNTRACED: Detect stopped (but not terminated) child processes
By default, waitpid() only returns when a child terminates.

With WUNTRACED: waitpid() also returns if a child process is stopped by a signal (e.g., SIGSTOP, CTRL+Z in a terminal).

🔹 Use case:
If you want to track when a child is paused (e.g., for job control in a shell).

WCONTINUED: Detect resumed child processes
Normally, waitpid() does not return when a child is resumed after being stopped.

With WCONTINUED: waitpid() returns if a stopped child is resumed via SIGCONT.

🔹 Use case:
Useful in shell-like programs that manage background jobs and need to track when a stopped job resumes.

Combining Flags
You can combine multiple options using the bitwise OR (|) operator:

c
Copy
Edit
waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED);
This:

Returns immediately if no child has exited (WNOHANG).

Returns if a child has stopped (WUNTRACED).

Returns if a stopped child resumes (WCONTINUED).


*/