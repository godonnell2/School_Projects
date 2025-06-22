#include "minishell.h"

void    print_tokens(t_token *head)
{
    t_token *token;

    token = head;
    write(1, "\nTokens: ", 9);
    while (token)
    {
        if (token->type == END)
            break ;
        write(1, "{", 1);
        write(1, token->token, token->len);
        write(1, "} ", 2);
        token = token->next;
    }
    write(1, "\n\n", 2);
}

void    print_commands(t_command *commands)
{
    int i;
    int j;
    int k;
    int l;
    int r;
    t_redirect *redir_in;
    t_redirect *redir_out;
    t_redirect *redirs;

    i = 0;
    while (commands != NULL)
    {
        j = 0;
        k = 0;
        l = 0;
        r = 0;
//        redir_in = commands->redir_in;
//        redir_out = commands->redir_out;
        redirs = commands->redirs;
        printf("commands[%i]\n", i);
/*         if (redir_in)
        {
            while (redir_in)
            {
                if (redir_in->type == REDIR_IN)
                    printf("redir_in[%i]: %s [INFILE]\n", k, redir_in->target);
                else if (redir_in->type == HEREDOC)
                    printf("redir_in[%i]: %s [HEREDOC] fd = %i\n", k, redir_in->target, redir_in->heredoc_fd);
                k++;
                redir_in = redir_in->next;
            }
        }
        if (redir_out)
        {
            while (redir_out)
            {
                if (redir_out->type == REDIR_OUT)
                    printf("redir_out[%i]: %s [OUTFILE]\n", l, redir_out->target);
                else if (redir_out->type == APPEND_OUT)
                    printf("redir_out[%i]: %s [APPEND_OUT]\n", l, redir_out->target);
                l++;
                redir_out = redir_out->next;
            }
        } */
        if (redirs)
        {
            while (redirs)
            {
                if (redirs->type == REDIR_IN)
                    printf("redirs[%i]: %s [INFILE]\n", r, redirs->target);
                else if (redirs->type == HEREDOC)
                    printf("redirs[%i]: %s [HEREDOC] fd = %i\n", r, redirs->target, redirs->heredoc_fd);
                else if (redirs->type == REDIR_OUT)
                    printf("redirs[%i]: %s [OUTFILE]\n", r, redirs->target);
                else if (redirs->type == APPEND_OUT)
                    printf("redirs[%i]: %s [APPEND_OUT]\n", r, redirs->target);
                r++;
                redirs = redirs->next;
            }
        }
        if (commands->args)
        {
            while (commands->args[j])
            {
                printf("args[%i]: %s\n", j, commands->args[j]);
                j++;
            }
        }
        printf("\n");
        i++;
        commands = commands->next;
    }
}