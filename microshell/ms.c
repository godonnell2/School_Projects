#include "microshell.h"

void ft_putstr_fd2(char *str, char *arg)
{
    while(*str)
        write(2, str++, 1);
    if(arg)
        while(*arg)
            write(2, arg++, 1);
    
    write(2, "\n",1); 
}

void ft_fatal_error(int fd)
{
    if(fd ==-1)
    {
        ft_putstr_fd2("error: fatal", NULL);
        exit(1);
    }
}

void ft_exec_child(char **av, int i, int tmp_fd , char **env)
{
   av[i]= NULL;

   ft_fatal_error(dup2(tmp_fd, STDIN_FILENO));
   close(tmp_fd);

   execve(av[0], av, env);
   ft_putstr_fd2("error: cannot execute", av[0]); //forgot error
   exit(1);

}

int main(int ac, char**av, char**env)
{
 int i = 0;
    int fd[2];
    (void) ac;
    pid_t pid;
    int tmp_fd = dup(STDIN_FILENO);
    ft_fatal_error(tmp_fd);
/*
while (argv[i] && argv[i + 1]) //check if the end is reached
	{
		// Advance to next command group
		argv = &argv[i + 1];	//the new argv start after the ; or |
		i = 0;

		// Find command boundaries: ; | or end of args
		//count until we have all informations to execute the next child;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
*/
   while (av[i] && av[i + 1]) //check if the end is reached
	{
		// Advance to next command group
		av = &av[i + 1];	//the new argv start after the ; or |
		i = 0;

		// Find command boundaries: ; | or end of args
		//count until we have all informations to execute the next child;
		while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
			i++;

        if(strcmp(av[0], "cd")==0)
        {
            if(i!=2)
                ft_putstr_fd2("error cd: bad arguments", NULL);
            else if(chdir(av[1])!= 0)
                ft_putstr_fd2("error: cannot change directory to ", av[1]);
        }
        else if(i!= 0 && (av[i] == NULL || strcmp(av[i], ";") ==0))
            {
                pid = fork();
                ft_fatal_error(pid);
                
                if(pid == 0)
                    ft_exec_child(av, i, tmp_fd, env);
                
                else
                {
                    close(tmp_fd);
                    while(waitpid(-1, NULL, WUNTRACED) != -1)
                            ;
                    tmp_fd = dup(STDIN_FILENO);
                    ft_fatal_error(tmp_fd);

                }
            }
        else if(i != 0 && (strcmp(av[i],"|")== 0))
        {
            ft_fatal_error(pipe(fd));
            pid = fork();
            ft_fatal_error(pid);
            if(pid == 0)
                 {
                    ft_fatal_error(dup2(fd[1], STDOUT_FILENO));
                    close(fd[1]);
                    close(fd[0]);
                    ft_exec_child(av, i, tmp_fd, env); 
                 }
            else
            {
                close(fd[1]);
                close(tmp_fd);
                tmp_fd = fd[0]; 
            }
        }
        
    }
    close(tmp_fd);
    return(0);
}