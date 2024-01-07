#include "../includes/headers/minishell.h"


void signal_handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;

	if (signal == SIGINT)
		ft_printf("\n");
	else if (signal == SIGQUIT)
		ft_printf("\n");
	else if (signal == SIGPIPE)
	{
		ft_printf("SIGPIPE\n");
		ft_printf("\n");
	}
		
}

void	change_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGPIPE, &sa, NULL);
}
