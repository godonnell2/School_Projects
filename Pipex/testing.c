
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        printf("Child: Starting\n");
        printf("Child: Calling exec to run sleep\n");
        execlp("sleep", "sleep", "2", NULL); // Replace process with 'sleep 2'
        perror("Child: Exec failed"); // Only runs if exec fails
       // No, that's what's so weird about exec! Your code will not run after the call to exec. 
       // Because you're replacing the process
      // That's why you need to fork first
    } else if (pid > 0) { // Parent process
        printf("Parent: Forked child with PID %d\n", pid);
        printf("Parent: Waiting for child\n");
        waitpid(pid, NULL, 0);
        // I asked chatgpt, the null is a PTR to the exit code of the child, in this case we don't 
        // care so we can pass NULL. 
       // The 0 are some flags? Maybe you can set a timeout or something
        printf("Parent: Child finished\n");
    } else {
        perror("Fork failed");
    }
    return 0;
}

//execlp seems to be a utility to use the PATH 
//to find the program, because "raw" exec requires the full path
//Execv is very similar except it doesn't use variable length arguments

/*
execve() replaces the current process, so nothing after it runs.
fork() creates a new process, allowing the parent to keep running while the child executes the new program.
For pipelines or any multi-step operations, fork() is essential to retain control in the parent process while 
executing commands in the children.

Key Points
The parent and child are separate processes after fork().
The parent continues running its own code, completely independent of what happens in the child.
The exec in the child replaces only the child process, so it does not affect the parent process.
The waitpid() call in the parent ensures the parent waits for the child to finish before proceeding
*/