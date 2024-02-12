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

void root_signals(void)
{
	struct sigaction sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0) 
		return;
	sigaction(SIGINT, &sa, NULL);
	ignore_signal(&sa, SIGQUIT);
}

void ignore_signal(struct sigaction *sa, int signal)
{
	struct sigaction	original_sa;
	int					original_flags;

	original_flags = sa->sa_flags;
	sa->sa_handler = SIG_IGN;
	sa->sa_flags |= SA_SIGINFO;
	if (sigemptyset(&sa->sa_mask) != 0)
		return;
	sigaction(signal, sa, &original_sa);
	sa->sa_flags = original_flags;
}
