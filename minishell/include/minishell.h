#ifndef MINISHELL_H
#define MINISHELL_H

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "debug.h"
#include <sys/ioctl.h>

#define OK 0
#define ERR_SYNTAX 1
#define ERR_MALLOC 2
#define ERR_OTHER 3

#define PATH_MAX 4096
#define READ 0
#define WRITE 1
#define STDIN 0
#define SPLIT_BUFF_SIZE 102400

volatile sig_atomic_t g_signal;

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
    HEREDOC_INPUT,
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

typedef struct s_redirect
{
    t_tok_type type; // HEREDOC, REDIR_IN, REDIR_OUT, APPEND_OUT
    char *target;    // redirect file or heredoc EOF
    int heredoc_fd;
    int heredoc_quoted;
    struct s_redirect *next;
} t_redirect;

typedef struct s_command
{
    char **args;
    t_redirect *redirs; // todo needed in order of parsing for test 108
    t_redirect *redir_in;
    t_redirect *redir_out;
    char *full_path;
    struct s_command *next;
} t_command;

typedef struct s_cmnd_lst
{
    t_command *head;
    t_command *tail;
} t_cmnd_lst;

typedef enum e_state
{
    IDLE,
    EXEC,
} t_state;

typedef struct s_shell
{
    t_env_vars *env_vars; // linked list of environment variables
    char **env_array;
    int last_exit_code;  // last exit code
    t_command *commands; // linked list of commands
    char *rl_input;      // command read from readline
    t_state state;
    // add signal things
} t_shell;

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
    t_shell *shell;
    t_tok_type  target_field;
    int         heredoc_quoted;
} t_parser_lst;

// EXECUTOR
typedef struct s_executor
{
    t_command *cmd_list; // head of list!!!
                         // t_command *curr_cmd; // the one being processed!!

    int last_exit_code; //// Used for $?
    int cmd_count;
    int cmd_i;
    char **env_array; // not sure i nede this here anymore need to double chek
    t_command *commands;
} t_executor;

typedef struct s_inherited_fds
{
    int *inherited_fds;
    int inherited_fds_count;
} t_inherited_fds;
typedef struct s_process
{
    t_command *cmd;
    t_inherited_fds *inherited_fds;
    int pid; // todo move pids?
    int in_fd;
    int out_fd;
} t_process;

typedef struct s_split_state
{
    size_t buff_offset;
    size_t word_count;
    char **arr;
    size_t word;
    size_t word_len;
} t_split_state;

// FILES

// main.c

//signals.c
void    signal_handler(int signo);
void    init_signal_handler(void);
void	ignore_signals_before_fork(void);
void	handle_signals_in_exec(int sig);
void	set_signals_to_default(void);
int    check_for_signals(t_shell *shell);

// parser_lst.c
int is_redirect(char c);
int is_pipe(char c);
char *strdup_len(char *str, int len);
int parser(t_shell *shell);
void print_env_vars(t_env_vars *env_vars);

// env_vars_init.c
void free_env_vars(t_env_vars *env_vars);
t_env_lst *env_var_new_tail_node(t_env_lst *list);
t_env_lst *add_env_var(char *envp_str, t_env_lst *list);
t_env_vars *get_env_vars(char **envp);

// tokenizer_utils.c
int tokenizer(t_parser_lst *list_params, char **command_str_ptr);
// static helper functions: tok_args, tok_redirect, tok_quotes, record_token_info

// token_utils.c
int is_operator_tok(t_tok_type type);
int is_arg_tok(t_tok_type type);
int is_redirect(char c);
int is_pipe(char c);
char *strdup_len(char *str, int len);

// expand_arg.c
char *expand_dquotes(t_token *token, t_parser_lst *list);
char *expand_arg(t_token *token, t_parser_lst *list);
char *process_arg_tok(t_token *token, t_parser_lst *list);

// expand_env.c
const char *get_env_var(t_env_vars *env_vars, const char *var, int len);
char *expand_env_var(char *ev, int *var_len, t_parser_lst *list);
char *append_ev_value(char *token_str, char *old_expanded_tok, int *i, t_parser_lst *list);
char *expand_all_env_vars(char *token_str, char *expanded_tok, t_parser_lst *list);
char *expand_env_vars(char *token_str, char *expanded_tok, t_tok_type type, t_parser_lst *list);

// list_utils.c
t_parser_lst *init_parser_lst(t_env_vars *env_vars, char *command, t_shell *shell);
int lst_add_empty_token_node(t_parser_lst *list);
t_command *lst_add_new_command(t_parser_lst *list);
void    lst_remove_last_command(t_parser_lst *list, t_command *command);
t_redirect *lst_add_new_redirect(t_command *command, t_tok_type type);
int add_arg_to_list(t_parser_lst *list_params, char *arg);

// testing.c
void print_tokens(t_token *head);
void print_commands(t_command *commands);

// free.c
void free_args_list(t_parser_lst *list);
void free_tokens_list(t_parser_lst *list);
void    free_command(t_command *command);
void free_commands_list(t_command *head);

// error.c
void error_free_and_exit(t_parser_lst *list, const char *error_message);
void syntax_error_free_parser_lst(t_parser_lst *list);
void print_syntax_error(t_tok_type type);

// GRACE!!!!!!!!!!!!!
// bis1.c
int ft_unset(t_env_vars **head, char *key);
int exit_shell(char **args, t_env_vars **env_list);
char *get_current_directory(char *buf, size_t size);
int ft_pwd(void);
int ft_echo(char **args);

// bis2.c
int ft_pwd(void);
int ft_export(t_env_vars **env_list, char **args);
int env(t_env_vars *head);
void clean_env_lst(t_env_vars **env_vars); // ASK BETH
t_env_vars *create_endnode(const char *key, const char *value);
int handle_export_arg(t_env_vars **env_list, char *arg);

// bis3_cd.c
int ft_cd(char **input, t_env_vars **env_list);

// bis_exec_check.c
int execute_builtin(t_command *command, t_env_vars **env_vars);
int is_built_in(t_command *cmd);

// heredoc.c
//int ft_heredoc(const char *delimiter);

// redirects.c
int get_heredoc_fd(t_command *cmd);

// path_access.c
int is_directory(const char *path);
void check_command_in_path(char **path_arr, char *cmd,
                           char *full_path);
char *get_env_path_variable(char **envp);
void resolve_command_full_path(t_shell *shell, char *cmd,
                               char *full_path);
void resolve_all_command_paths(t_shell *shell, t_command *cmds);

// executor.c
int is_built_in(t_command *cmd);
void execute_pipes(t_command *cmds, char **env_arr, t_env_vars *env_vars, t_shell *shell);
void close_if_not_std(int fd);

// helper.c
int ft_strcmp(const char *s1, const char *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_wordlen(char *s);
void ft_putstring_fd(char *s, int fd);

// helperbis2.c
int is_numeric(const char *str);
int is_valid_identifier_var(const char *name);
void print_invalid_identifier_error(const char *arg);

// split_buff_path.c
char *cat_strs_char(char *dest, const char *src1, char c, const char *src2);
void ft_strcpy(char *src, char *dst);
char **ft_split_buff(char const *s, char sep, void *buff);

// env_nodes.c
char *get_env_value(t_env_vars *env_vars, const char *key);
t_env_vars *extract_node(t_env_vars **head, char *key);
int count_env_nodes(t_env_vars *env_vars);
void update_env_var(t_env_vars **env_list, const char *key, const char *value);
void clean_env_lst(t_env_vars **env_vars);

// env_arr.c
void free_env_array(char **env_array);
char **convert_env_to_array(t_env_vars *env_vars);

void init_proc(t_process *proc, t_command *cmd);
void close_if_not_std(int fd);
int apply_redirections(t_process *proc, t_shell *shell);
void set_exit_code(t_shell *shell, int code);
#endif