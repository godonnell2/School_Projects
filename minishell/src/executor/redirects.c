#include "minishell.h"

// If heredoc_fd is set, we need to USE that and IGNORE infile.
// otherwise we can fallback to infile
// THIS SHOULD WORK FOR

// bitwise ops
//  write only for curr process
//  TRUNC does not append it overwrites,
//  needs to clear it otherwise when writing could have left over bits
//  0 means its in octal form (base 8)
//  6 owner Read (4) + Write (2) = 6
// 4 group Read (4) = 4
//  4 others Read (4) = 4
// in this case target is the filname
// Only dup2 the LAST redirection!!!!
/*
Priority	Source	Example
1	Heredoc	cat <<EOF
2	< file	cat < file.txt
3	Pipe input	`echo hello but it shouuld be like this
*/
 /* close_if_not_std(in_fd);
            in_fd = ft_heredoc(redir->target); */
//implemented in parser_lst.c (see add_redirection_arg -> get_heredoc -> heredoc_var_expansion)

static int process_redirection(t_redirect *redir, int *in_fd, int *out_fd)
{
    if (redir->type == REDIR_IN)
    {
        close_if_not_std(*in_fd);
        *in_fd = open(redir->target, O_RDONLY);
        return (*in_fd);
    }
    else if (redir->type == HEREDOC)
    {
        close_if_not_std(*in_fd);
        *in_fd = redir->heredoc_fd;
        return (*in_fd);
    }
    else if (redir->type == REDIR_OUT)
    {
        close_if_not_std(*out_fd);
        *out_fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        return (*out_fd);
    }
    else if (redir->type == APPEND_OUT)
    {
        close_if_not_std(*out_fd);
        *out_fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
        return (*out_fd);
    }
    return (0);  // Not a redirection type we handle
}

int apply_redirections(t_process *proc, t_shell *shell)
{
    t_redirect *redir = proc->cmd->redirs;
    int in_fd = proc->in_fd;
    int out_fd = proc->out_fd;
    int fd_result;

    while (redir)
    {
        fd_result = process_redirection(redir, &in_fd, &out_fd);
        
        if (fd_result < 0)
        {
            DEBUG_LOG("Redirection error on %s", redir->target);
            perror(redir->target);
            shell->last_exit_code = 1;
            return (-1);
        }
        redir = redir->next;
    }
    proc->in_fd = in_fd;
    proc->out_fd = out_fd;
    return (0);
}

// Main initialization function
void init_proc(t_process *proc, t_command *cmd)
{

    proc->cmd = cmd;
    proc->pid = -1;
    proc->in_fd = STDIN_FILENO;
    proc->out_fd = STDOUT_FILENO;

}

//DEBUG_LOG("init_proc for command '%s'\n", cmd->args ? cmd->args[0] : "NULL_CMD");