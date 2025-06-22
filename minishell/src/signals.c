#include "minishell.h"

void    init_signal_handler(void)
{
    struct sigaction	sa;

    sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	ignore_signals_before_fork(void) //temporarily ignoring signals in the parent
{
	struct sigaction sa_ignore;
	
	ft_memset(&sa_ignore, 0, sizeof(struct sigaction));
	sa_ignore.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_ignore, NULL);
	sigaction(SIGQUIT, &sa_ignore, NULL);
}

void	set_signals_to_default(void) //resetting default signal behaviour for child process
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);// Reset SIGINT to default
	sigaction(SIGQUIT, &sa, NULL);// Reset SIGQUIT to default
}

void	handle_signals_in_exec(int sig)
{
	if (sig == SIGINT) //printing standard behaviour per sig type.
		write(1, "\n", 1);
	if (sig == SIGQUIT)
		write(1, "Quit: 3\n", 8); //what text do we need here?
	init_signal_handler();
}

void    signal_handler(int signo)
{
    char    nl;

    g_signal = signo;
	if (signo == SIGQUIT)
		return ;
    nl = '\n';
    ioctl(STDIN_FILENO, TIOCSTI, &nl);
}

int    check_for_signals(t_shell *shell)
{
    if (g_signal == 0)
        return (0);
	if (g_signal == SIGQUIT)
    {
		DEBUG_PRINTF("Ignoring SIGQUIT\n");
		return (0);
	}
    else if (g_signal == SIGINT)
    {
        DEBUG_PRINTF("Received SIGINT\n");
        rl_replace_line("", 0);
        rl_on_new_line();
		free(shell->rl_input);
/* 		if (shell->state == EXEC)
		{
			printf("redisplaying\n");
			rl_redisplay();
		} */
    }
	return (1);
}