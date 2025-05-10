#include "minishell.h"

//parser just prints result, no execution
//cc -Wall -Wextra -lreadline libft/ft_split.c libft/ft_strjoin.c parser.c
int is_redirect(char c)
{
    return (c == '>' || c == '<');
}

int is_pipe(char c)
{
    return (c == '|');
}

char *strdup_len(char *str, int len)
{
    char *dst;
    int i;

    dst = malloc(sizeof(char) * (len + 1));
    if (dst == NULL)
        return (NULL);
    i = 0;
    while (i < len)
    {
        dst[i] = str[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

//adds tokens found in chunk to the command table
void    add_command(t_token *token, t_command *command_table, int args_count)
{
    int i;

    i = 0;
    command_table->args = malloc(sizeof(char *) * (args_count + 1)); //NULL CHECK
    while (token->type != PIPE && token->type != END_OF_COMMANDS)
    {
        if (token->type == REDIR_IN)
        {
            token++;
            command_table->infile = strdup_len(token->token, token->len); //NULL CHECK
        }
        else if (token->type == REDIR_OUT || token->type == APPEND_OUT)
        {
            if (token->type == APPEND_OUT)
                command_table->append_out = 1;
            token++;
            command_table->outfile = strdup_len(token->token, token->len); //NULL CHECK
        }
        else if (token->type == ARGS || token->type == D_QUOTES)
        {
            command_table->args[i] = strdup_len(token->token, token->len); //NULL CHECK
            i++;
        }
        token++;
    }
    command_table->args[i] = NULL;
}

t_command    *parse_commands(char *command, t_command *commands, int *commands_index)
{
    static t_token tokens[50];
 //   static t_command commands[5];
    t_token *chunk_start;
    int i;
    int j;
    int args_count;
    int total_tokens;

    //tokenizer
    i = 0;
    j = 0;
    args_count = 0;
    total_tokens = 0;
    chunk_start = &tokens[0];
    while (command[i] && j < 49)
    {
        //skip white spaces
        while (command[i] == ' ')
            i++;
        //record token
        tokens[j].token = &command[i];
        if (command[i] == '"')
        {
            tokens[j].type = D_QUOTES;
            tokens[j].len = 1;
            i++;
            while (command[i] != '"' && command[i])
            {
                i++;
                tokens[j].len++;
            }
            if (command[i] == '"')
            {
                i++;
                tokens[j].len++;
            }
            args_count++;
        }
        else if (is_pipe(command[i]))
        {
            tokens[j].type = PIPE;
            tokens[j].len = 1;
            i++;
            //when a pipe is encountered, populate the command table and prepare for new chunk
            add_command(chunk_start, &commands[*commands_index], args_count);
            args_count = 0;
            *commands_index += 1;
            chunk_start = &tokens[j + 1];
        }
        else if (is_redirect(command[i]))
        {
            if (command[i] == '<' && command[i + 1] == '<')
            {
                tokens[j].type = HEREDOC;
                tokens[j].len = 2;
                i++;
            }
            else if (command[i] == '<')
            {
                tokens[j].type = REDIR_IN;
                tokens[j].len = 1;
            }
            else if (command[i] == '>' && command[i + 1] == '>')
            {
                tokens[j].type = APPEND_OUT;
                tokens[j].len = 2;
                i++;
            }
            else if (command[i] == '>')
            {
                tokens[j].type = REDIR_OUT;
                tokens[j].len = 1;
            }
            i++;
        }
        else
        {
            tokens[j].type = ARGS;
            tokens[j].len = 0;
            while (command[i] && command[i] != ' ' && !is_pipe(command[i] && !is_redirect(command[i]) && command[i]!= '"'))
            {
                tokens[j].len++;
                i++;
            }
            args_count++;
        }
        j++;
        total_tokens++;
    }
    tokens[j].type = END_OF_COMMANDS;
    tokens[j].token = NULL;
    add_command(chunk_start, &commands[*commands_index], args_count);
    i = 0;
    j = 0;
    //print tokens
    write(1, "\nTokens: ", 9);
    while (j < total_tokens)
    {
        write(1, "{", 1);
        write(1, tokens[j].token, tokens[j].len);
        write(1, "} ", 2);
        //printf("[%i]\n", tokens[j].type);
        j++;
    }
    write(1, "\n\n", 2);
    return (NULL);
}

void    clear_table_buffer(t_command *commands, int *last_index)
{
    int i;
    int j;

    i = 0;
    while (i <= *last_index)
    {
        j = 0;
        while (commands[i].args[j])
        {
            free(commands[i].args[j]);
            j++;
        }
        commands[i].args = NULL;
        if (commands[i].infile)
        {
            free(commands[i].infile);
            commands[i].infile = NULL;
        }
        if (commands[i].outfile)
        {
            free(commands[i].outfile);
            commands[i].outfile = NULL;
        }
        commands[i].append_out = 0;
        i++;
    }
    *last_index = 0;
}

#define SPLIT_BUFF_SIZE 1024 //
int main(void)
{
    static t_command   commands[10];
    static int         commands_index;
    int i;
    int j;
    char *input;
 char some_buffer[SPLIT_BUFF_SIZE]; // Buffer for splitting commands
    char some_other_buffer[SPLIT_BUFF_SIZE]; // Buffer for splitting arguments

    while (1) 
    {
        input = readline("minishell> ");
        if (input == NULL)
        {
            printf("\n");
            break;
        }
        else if (strcmp(input, "exit") == 0)
        {
            free(input);
            break;
        }
        else
        {
            add_history(input);
            //tokenize input and parse to commands table
            parse_commands(input, &commands[0], &commands_index);
            i = 0;
            //print commands table
            while (i <= commands_index)
            {
                j = 0;
                printf("commands[%i] infile: %s, outfile: %s, append?: %i\n", i, commands[i].infile, commands[i].outfile, commands[i].append_out);
                while (commands[i].args[j])
                {
                    printf("arg[%i]: %s\n", j, commands[i].args[j]);
                    j++;
                }
                printf("\n");
                i++;
            }
            
            if (commands_index > 0) {
            // Execute all parsed commands
            execute_pipes(commands, commands_index, envp);
        }
        // Clear the commands buffer for next input
        clear_table_buffer(commands, &commands_index);
            free(input);
/*             if (commands_index == 0)
                execute_command(commands->args, envp);
            else
                execute_pipes(commands, commands_index + 1, envp); */
            clear_table_buffer(&commands[0], &commands_index);
        }
    }
    return (0);
}