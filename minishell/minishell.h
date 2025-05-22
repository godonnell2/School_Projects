#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>

#define PATH_MAX 4096
#define READ 0
#define WRITE 1
#define STDIN 0
#define SPLIT_BUFF_SIZE 102400

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

// PARSER
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
    END,
} t_tok_type;

typedef struct s_token
{
    char *token;
    t_tok_type type;
    int len;
    int prev_white_space;
    struct s_token *next;
} t_token;

typedef struct s_arg
{
    char *arg;
    struct s_arg *next;
} t_arg;

typedef struct s_command
{
    char **args;
    char *infile;
    char *outfile;
    int append_out;
    char *heredoc_eof;
    int heredoc_fd;
    char *full_path;
    struct s_command *next;
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
    t_token *current_token;
    t_arg *arg_head;
    t_arg *arg_tail;
    t_command *command_head;
    t_command *command_tail;
    t_env_vars *env_vars;
    char *readline_command;
} t_parser_lst;

// EXECUTOR
typedef struct s_executor
{
    t_command *cmd_list; // head of list!!!
                         // t_command *curr_cmd; // the one being processed!!
    // int pipe_fd[2];
    // int prev_pipe_fd;
    // pid_t *pids;
    // int pid_index;
    int last_exit_code; //// Used for $?
    int cmd_count;
    int cmd_i;
    char **env_array; // not sure i nede this here anymore need to double chek
    t_command *commands;
} t_executor;
typedef struct s_child_process
{
    t_command *cmd;
    int pid; // todo move pids?
    int pipe_fd[2];
} t_child_process;

typedef struct s_split_state
{
    size_t buff_offset;
    size_t word_count;
    char **arr;
    size_t word;
    size_t word_len;
} t_split_state;

// FILES
// parser_lst.c
int is_redirect(char c);
int is_pipe(char c);
char *strdup_len(char *str, int len);
t_command *parser(char *command, t_command *commands_head, t_env_vars *env_vars);

// env_vars_init.c
void free_env_vars(t_env_vars *env_vars);
t_env_lst *env_var_new_tail_node(t_env_lst *list);
t_env_lst *add_env_var(char *envp_str, t_env_lst *list);
t_env_vars *get_env_vars(char **envp);

// tokenizer_utils.c
char *tokenizer(t_parser_lst *list_params, char *command);
// static helper functions: tok_args, tok_redirect, tok_quotes, record_token_info

// token_utils.c
int is_operator_tok(t_tok_type type);
int is_arg_tok(t_tok_type type);
int is_redirect(char c);
int is_pipe(char c);
char *strdup_len(char *str, int len);

// expand_arg.c
char *expand_dquotes(t_token *token, t_env_vars *env_vars);
char *expand_arg(t_token *token, t_parser_lst *list);
char *process_arg_tok(t_token *token, t_parser_lst *list);

// expand_env.c
const char *get_env_var(t_env_vars *env_vars, const char *var, int len);
char *expand_env_var(char *ev, int *var_len, t_env_vars *env_vars);
char *append_ev_value(char *token_str, char *old_expanded_tok, int *i, t_env_vars *env);
char *expand_all_env_vars(char *token_str, char *expanded_tok, t_env_vars *env);

// list_utils.c
t_parser_lst *init_parser_lst(t_env_vars *env_vars, char *command);
t_parser_lst *lst_add_empty_token_node(t_parser_lst *list_params);
t_command *lst_add_new_command(t_parser_lst *list);
t_parser_lst *add_arg_to_list(t_parser_lst *list_params, char *arg);

// testing.c
void print_tokens(t_token *head);
void print_commands(t_command *commands);

// free.c
void free_args_list(t_parser_lst *list);
void free_tokens_list(t_parser_lst *list);
void free_commands_list(t_command *head);
void error_free_parser_lst(t_parser_lst *list);

// error.c
void error_free_and_exit(t_parser_lst *list, const char *error_message);
void print_syntax_error(t_tok_type type);

// GRACE!!!!!!!!!!!!!
// bis2.c
int ft_cd(char **input, t_env_vars **env_list);
int ft_echo(char **args);
int ft_pwd(void);
int ft_unset(t_env_vars **head, char *key);
int ft_export(t_env_vars **env_list, char **args);
int env(t_env_vars *head);
int exit_shell(char **args, t_env_vars **env_list);
void clean_env_lst(t_env_vars **env_vars); // ASK BETH
int ft_isalnum(int c);
t_env_vars *create_endnode(const char *key, const char *value);
char *get_env_value(t_env_vars *env_vars, const char *key); // ASK BETH ADD DUP LATTER FIX
int ft_heredoc(const char *delimiter);
void update_env_var(t_env_vars **env_list, const char *key, const char *value);
t_env_vars *extract_node(t_env_vars **head, char *key);

// executor.c
void check_command_in_path(char **path_arr, char *cmd,
                           char *full_path);
char *get_env_path_variable(char **envp);
void resolve_command_full_path(t_env_vars *env_vars, char *cmd,
                               char *full_path);
void resolve_all_command_paths(t_env_vars *env_vars, t_command *cmds);
int is_built_in(t_command *cmd);
char **convert_env_to_array(t_env_vars *env_vars);
void execute_pipes(t_command *cmds, char **env_arr, t_env_vars *env_vars);

// helper.c
int ft_strcmp(const char *s1, const char *s2);

#endif