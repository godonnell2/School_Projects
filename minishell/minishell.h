#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
//# include "libft/libft.h"

# define PATH_MAX 4096
 //token types
 /*
# define ARGS 0
# define REDIR_IN 1
# define REDIR_OUT 2
# define APPEND_OUT 3
# define HEREDOC 4
# define PIPE 5
# define D_QUOTES 6
# define S_QUOTES 7
# define END_OF_COMMANDS 8 
*/

//replacing with enums
typedef enum e_tok_type 
{
    ARGS,
    REDIR_IN,
    REDIR_OUT,
    APPEND_OUT,
    HEREDOC,
    PIPE,
    D_QUOTES,
    S_QUOTES,
    END_OF_COMMANDS
} t_tok_type;

typedef struct s_env_vars 
{
    char *key;
    char *value;
    struct s_env_vars *next;
} t_env_vars;

typedef struct s_env_lst
{
    t_env_vars *head;
    t_env_vars *tail;
    t_env_vars *current;
} t_env_lst;

typedef struct s_token
{
    char            *token;
    t_tok_type      type;
    int             len;
    int             prev_white_space;
    struct s_token  *next;
} t_token;

typedef struct s_token_lst
{
    t_token *head;
    t_token *tail;
    t_token *chunk_head;
} t_token_lst;

typedef struct s_arg
{
    char    *arg;
    struct s_arg *next;
} t_arg;

typedef struct s_command
{
    char **args;
    char *infile;
    char *outfile;
    int append_out;
    char *heredoc_eof; // we have it!!
     int  heredoc_fd;  // Ask beth could we add this??  and init to -1
    struct s_command *next;
    char *full_path; //ask beth can we add this to the struct
} t_command;

typedef struct s_cmnd_lst
{
    t_command *head;
    t_command *tail;
} t_cmnd_lst;

typedef struct s_parser_lst
{
    t_token *token_head;
    t_token *token_tail;
    t_token *chunk_head;
    t_arg   *arg_head;
    t_arg   *arg_tail;
    int     args_count;
    t_command *command_head;
    t_command *command_tail;
    t_env_vars *env_vars;
} t_parser_lst;

// //ft_split.c
// char	**ft_split(char *str, char delim);
// void	free_array(char **str_array, int index);

// //ft_strjoin.c
// char	*ft_strjoin(char const *s1, char const *s2);
// int		ft_strlen(const char *s);

// //ft_strdup.c
// char	*ft_strdup(const char *s1);

// //ft_memset.c
// void	*ft_memset(void *b, int c, size_t len);

// //ft_strchr.c
// char	*ft_strchr(const char *s, int c);

//parser_exec_utils.c
int     count_str_in_array(char **str_array);
char    *malloc_error(char **paths);
char    *find_command_path(char *cmd, char **envp);
void    execute_command(char **args, char **envp);
void execute_pipes(t_command *cmds, int num_cmds, char **env_arr, t_env_vars *env_vars);

//parser_exec.c
int     is_redirect(char c);
int     is_pipe(char c);
char    *strdup_len(char *str, int len);
//void    add_command(t_token *token, t_command *command_table, int args_count);
//t_command    *parse_commands(char *command, t_command *commands, int *commands_index);
void    clear_table_buffer(t_command *commands, int *last_index);

//env_vars_init.c
void        free_env_vars(t_env_vars *env_vars);
t_env_lst*  env_var_new_tail_node(t_env_lst *list);
t_env_lst*  add_env_var(char *envp_str, t_env_lst *list);
void update_env_var(t_env_vars **env_list, const char *key, const char *value); //wont create if it doesnt arlready exist ASK BETH
void initialize_env_list(t_env_vars **env_list); //CAN WE ADD BETH?
t_env_vars* get_env_vars(char **envp);
void print_env_vars(t_env_vars *env_vars);
t_env_vars *get_env_node(t_env_vars *env_vars, const char *key);//OK TO ADD BETH??? 
void set_env_var(t_env_vars **env_list, const char *key, const char *value); // OK TO ADD doesnt update unconfidiotnally



//HELPER//
int ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s);
int ft_strlen(const char *str);
void    *ft_memcpy(void *dest, const void *src, size_t n);
char    *ft_strchr(const char *s, int c);
int ft_isalpha(int c);
 int ft_isdigit(int c);
 int	is_numeric(const char *str);

// BUILTINS
int	ft_cd(char **input, t_env_vars **env_list);
int ft_echo(char **args);
int ft_pwd(void);
int ft_unset(t_env_vars **head, char *key);
int ft_export(t_env_vars **env_list, char **args);
int env(t_env_vars *head);
int	exit_shell(char **args, t_env_vars **env_list);
void clean_env_lst(t_env_vars **env_vars); //ASK BETH
int ft_isalnum(int c);
t_env_vars *create_endnode(const char *key, const char *value);
char *get_env_value(t_env_vars *env_vars, const char *key); //ASK BETH ADD

int ft_heredoc(const char *delimiter);


#endif