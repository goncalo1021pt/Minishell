#include "../includes/headers/minishell.h"


void signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;

	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGPIPE)
	{
		ft_printf("\0");
	}
}

void	root_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;

	sigaction(SIGINT, &sa, NULL);
	ignore_signal(&sa, SIGQUIT);
}

void	ignore_signal(struct sigaction *sa, int signal)
{
	sa->sa_handler = SIG_IGN;
	sigaction(signal, sa, NULL);
	
}
