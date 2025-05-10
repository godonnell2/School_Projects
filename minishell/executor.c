#include <stdio.h> //has to come before readline 
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "minishell.h"
#define READ 0
#define WRITE 1
#define STDIN 0
# define SPLIT_BUFF_SIZE 102400


typedef struct s_executor 
{
    int     pipe_fd[2];     
    int     prev_pipe_fd;   
    int     last_exit_code; 
    pid_t   *pids;         
    
} t_executor;


typedef struct s_split_state 
{
    size_t buff_offset;
    size_t word_count;
    char **arr;
    size_t word;
    size_t word_len;
} t_split_state;

// Function prototypes
void *ft_memcpy(void *dest, const void *src, size_t n);
void check_command_in_path(char **path_arr, char *cmd, char *full_path);
char *get_env_path_variable(char **envp);
void resolve_command_full_path(t_env_vars *env_vars, char *cmd, char *full_path);



int	ft_wordlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s[i] != ' ')
		i++;
	return (i);
}

void	ft_putstring_fd(char *s, int fd)
{
	write(fd, s, ft_wordlen(s));
}

char *strndup(const char *s, size_t n) {
    char *d = malloc(n + 1);
    if (!d) return NULL;
    ft_memcpy(d, s, n);
    d[n] = '\0';
    return d;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*cs1;
	unsigned char	*cs2;

	i = 0;
	cs1 = (unsigned char *)s1;
	cs2 = (unsigned char *)s2;
	while (i < n && (cs1[i] || cs2[i]))
	{
		if (cs1[i] != cs2[i])
		{
			return (cs1[i] - cs2[i]);
		}
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = (const unsigned char *)src;

	d = (unsigned char *)dest;
	while (n--)
	{
		*d++ = *s++;
	}
	return (dest);
}

void	ft_strcpy(char *src, char *dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*cat_strs_char(char *dest, const char *src1, char c, const char *src2)
{
	size_t	i;

	i = 0;
	if (!src1 || !src2)
	{
		return (NULL);
	}
	while (*src1)
	{
		dest[i++] = *src1++;
	}
	dest[i++] = c;
	while (*src2)
	{
		dest[i++] = *src2++;
	}
	dest[i] = '\0';
	return (dest);
}

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	word_count;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			word_count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (word_count);
}

static void	skip_separators(const char **s, char sep)
{
	while (**s == sep)
	{
		(*s)++;
	}
}

char	**ft_split_buff(char const *s, char sep, void *buff)
{
	const char		*start;
	t_split_state	curr;

	curr.buff_offset = 0;
	curr.word_count = count_words(s, sep);
	curr.arr = (char **)(buff + curr.buff_offset);
	curr.buff_offset += sizeof(char *) * (curr.word_count + 1);
	curr.word = 0;
	while (*s)
	{
		skip_separators(&s, sep);
		start = s;
		while (*s && *s != sep)
			s++;
		curr.word_len = s - start;
		if (curr.buff_offset + curr.word_len + 1 > SPLIT_BUFF_SIZE)
			return (NULL);
		curr.arr[curr.word] = (char *)buff + curr.buff_offset;
		ft_memcpy(curr.arr[curr.word], start, curr.word_len);
		curr.arr[curr.word++][curr.word_len] = '\0';
		curr.buff_offset += curr.word_len + 1;
		skip_separators(&s, sep);
	}
	curr.arr[curr.word] = NULL;
	return (curr.arr);
}



  
char **convert_env_to_array(t_env_vars *env_vars) {
    int count = 0;
    t_env_vars *current = env_vars;
    
    while (current) {
        count++;
        current = current->next;
    }
    
    char **env_array = malloc(sizeof(char *) * (count + 1));
    if (!env_array) return NULL;
    
    current = env_vars;
    int i = 0;
    while (current) {
        env_array[i] = malloc(ft_wordlen(current->key) + ft_wordlen(current->value) + 2);
        printf("ENV: %s=%s\n", current->key, current->value);
        if (!env_array[i]) {
            while (i-- > 0) free(env_array[i]);
            free(env_array);
            return NULL;
        }
        int len_key = ft_wordlen(current->key);
         ft_strcpy(env_array[i], current->key);
        env_array[i][len_key] = '=';          
        ft_strcpy(env_array[i] + len_key + 1, current->value); 
        current = current->next;
        
        i++;
    }
    env_array[i] = NULL;
    return env_array;
} 

static int execute_builtin(t_command *command, t_env_vars *env_vars)
{
    (void)env_vars;
    if (ft_strcmp(command->args[0], "cd") == 0)
    {
       return ft_cd(command->args[0], &env_vars);
       
    }
     else if (ft_strcmp(command->args[0], "echo") == 0)
    {
       return  ft_echo(command->args);
       
    }
    else if (ft_strcmp(command->args[0], "pwd") == 0)
    {
       return  ft_pwd();
     }
    // else if (ft_strcmp(command->args[0], "export") == 0)
    // {
    //    return  export_env_var(env_vars, command->args, command->args);
            
    // }
    // else if (ft_strcmp(command->args[0], "unset") == 0)
    // {   
    //   return ft_unset(&env_vars, command->args);     
    // }
    else if (ft_strcmp(command->args[0], "env") == 0)
    {
        return  env(env_vars);
    }
    else if (ft_strcmp(command->args[0], "exit") == 0)
    {
        return exit_shell(&env_vars);

    }
    return 2;
    
}

char *get_path_variable(t_env_vars *env_vars) {
    t_env_vars *current = env_vars;
    while (current != NULL) {
        if (ft_strncmp(current->key, "PATH", 5) == 0) {
            return current->value;
        }
        current = current->next;
    }
    return NULL;
}

void	check_command_in_path(char **path_arr, char *cmd, char *full_path)
{
	size_t	p_len;
	size_t	c_len;
	char	**temp_patharr;

	temp_patharr = path_arr;
	while (*temp_patharr != NULL)
	{
		p_len = ft_wordlen(*temp_patharr);
		c_len = ft_wordlen(cmd);
		if ((p_len + c_len + 2) > PATH_MAX)
			return ;
		cat_strs_char(full_path, *temp_patharr, '/', cmd);
		if (access(full_path, X_OK) == 0)
			return ;
		temp_patharr++;
	}
	full_path[0] = '\0';
}


void resolve_command_full_path(t_env_vars *env_vars, char *cmd, char *full_path) 
{
    char buff[SPLIT_BUFF_SIZE];
    char **path_arr;
    char *path_env;

    full_path[0] = '\0';
    if (access(cmd, X_OK) == 0) {
        ft_strcpy(cmd, full_path);
        return;
    }
    
    path_env = get_path_variable(env_vars);
    if (!path_env)
        return;
    
    path_arr = ft_split_buff(path_env, ':', buff);
    check_command_in_path(path_arr, cmd, full_path);
}

static void setup_redirections(t_command *cmd) 
{
    if (cmd->infile) 
    {
        int fd = open(cmd->infile, O_RDONLY);
        if (fd < 0) 
        {
            perror(cmd->infile);
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    int flags = 0;
    if (cmd->outfile) 
    {
       if (cmd->append_out) 
        {
            flags = O_APPEND | O_CREAT | O_WRONLY;
        } 
        else 
        {
            flags = O_TRUNC | O_CREAT | O_WRONLY;
        }
        int fd = open(cmd->outfile, flags, 0644);
        if (fd < 0) 
        {
            perror(cmd->outfile);
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }
}

void execute_pipes(t_command *commands, int num_commands,char **env_array) 
{
    t_executor exec;
    int i = 0;

    exec.prev_pipe_fd = -1;
    exec.pids = malloc(sizeof(pid_t) * num_commands);

    while (i < num_commands) 
    {
        if (i < num_commands - 1) 
        {
            if (pipe(exec.pipe_fd) < 0) 
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        exec.pids[i] = fork();
        if (exec.pids[i] < 0) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (exec.pids[i] == 0) 
        { // Child process
            // Set up input from previous pipe (if not first command)
            if (i > 0) 
            {
                dup2(exec.prev_pipe_fd, STDIN_FILENO);
                close(exec.prev_pipe_fd);
            }
            // Set up output to next pipe (if not last command)
            if (i < num_commands - 1) 
            {
                dup2(exec.pipe_fd[WRITE], STDOUT_FILENO);
                close(exec.pipe_fd[WRITE]);
            }
            // Handle redirections (infile/outfile)
            setup_redirections(&commands[i]);
            // Execute command
            execve(commands[i].full_path, commands[i].args, env_array);
            perror("execve");
            exit(EXIT_FAILURE);
        } 
        else
         { // Parent process
            // Close previous pipe (if any)
            if (i > 0) 
            {
                close(exec.prev_pipe_fd);
            }
            // Save current pipe's read end for next command
            if (i < num_commands - 1) 
            {
                close(exec.pipe_fd[WRITE]);
                exec.prev_pipe_fd = exec.pipe_fd[READ];
            }
            i++;
        }
    }

    // Wait for all children and capture exit codes
    for (i = 0; i < num_commands; i++) {
        int status;
        waitpid(exec.pids[i], &status, 0);
        if (WIFEXITED(status))
            exec.last_exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            exec.last_exit_code = 128 + WTERMSIG(status);
    }
    free(exec.pids);
}

// void setup_commands(t_command *commands)
// {
//     commands[0].args = malloc(sizeof(char *) * 3);
 
//     commands[0].args[0] = strdup("ls");
//     commands[0].args[1] = strdup("-l");
//     commands[0].args[2] = NULL;
//     commands[0].infile = NULL;
//     commands[0].outfile = NULL;
//     commands[0].append_out = 0;
// }

// void setup_commands(t_command *commands)
// {
//     commands[0].args = malloc(sizeof(char *) * 4);
 
//     commands[0].args[0] = strdup("echo");
//     commands[0].args[1] = strdup("-n");
//     commands[0].args[2] = "this is a test";
//     commands[0].args[3] = NULL;
//     commands[0].infile = NULL;
//     commands[0].outfile = NULL;
//     commands[0].append_out = 0;
//     commands[0].full_path = NULL;
// }

void setup_commands(t_command *commands)
{
    commands[0].args = malloc(sizeof(char *) * 3);
 
    commands[0].args[0] = strdup("cd");
    commands[0].args[1] = NULL;
    commands[0].args[2] = NULL;
    commands[0].infile = NULL;
    commands[0].outfile = NULL;
    commands[0].append_out = 0;
    commands[0].full_path = NULL;
}


int main(void)
{
        // 1. Create a mock envir lst
    t_env_vars *home_var = malloc(sizeof(t_env_vars));
    home_var->key = strdup("HOME");
    home_var->value = strdup("/Users/grace");
    home_var->next = NULL;
    t_env_vars *env_vars = malloc(sizeof(t_env_vars));
    env_vars->key = strdup("PATH");
    env_vars->value = strdup("/bin:/usr/bin:/usr/local/bin");
    env_vars->next = home_var ;
    

    int num_commands = 1; 
    t_command *commands = malloc(sizeof(t_command) * num_commands);

    setup_commands(commands);

   if (ft_strcmp(commands[0].args[0], "pwd") != 0) 
   {  // Only resolve for non-builtins
        char full_path[PATH_MAX];
        resolve_command_full_path(env_vars, commands[0].args[0], full_path);
        if (full_path[0] != '\0') 
        {
            commands[0].full_path = strdup(full_path);
        }
    }
    // 4. Exec builitins
    char current_dir[PATH_MAX];
    if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
        printf("Current Directory (Before cd): %s\n", current_dir);
    } else {
        perror("getcwd");
    }
    int exit_code = execute_builtin(&commands[0], env_vars);
    printf("--- After execute_builtin ---\n");
    printf("Exit code from execute_builtin: %d\n", exit_code);
     if (getcwd(current_dir, sizeof(current_dir)) != NULL) {
        printf("Current Directory (After cd): %s\n", current_dir);
    } else {
        perror("getcwd");
    }


    //exec pipes
    if (exit_code == 2) 
    {  // Not a builtin, use execve
        char **env_array = convert_env_to_array(env_vars);
        int exit_code = execute_builtin(commands, env_vars);
        // NEED TO CAPTURE EXIT CODE FROM BELOW TOO!!
        execute_pipes(commands, num_commands, env_array);
        free(env_array);
    }
    printf("exit_code: %i", exit_code);
    // free everythihg in reality 
    return exit_code ;
}