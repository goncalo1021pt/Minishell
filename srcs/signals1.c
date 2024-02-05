#include "../includes/headers/minishell.h"

void root_handler(int signum, siginfo_t *info, void *ptr)
{
	(void)info;
	(void)ptr;
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void ignore_signal(struct sigaction *sa, int signal) 
{
	struct sigaction	original_sa;
	int					original_flags;

	original_flags = sa->sa_flags;
	sa->sa_handler = SIG_IGN;
	sa->sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa->sa_mask) != 0)
		return;
	sigaction(signal, sa, &original_sa);
	sa->sa_flags = original_flags;
}

void root_setup_signals(void)
{
	struct sigaction sa;

	sa.sa_sigaction = root_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0) 
		return;
	sigaction(SIGINT, &sa, NULL);
	ignore_signal(&sa, SIGQUIT);
}

void child_handler(int signum, siginfo_t *info, void *ptr)
{
	(void)info;
	(void)ptr;
	if (signum == SIGINT)
	{
		// sergio part
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void child_setup_signals(void)
{
	struct sigaction sa;

	sa.sa_sigaction = child_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) != 0) 
		return;
	sigaction(SIGINT, &sa, NULL);
	ignore_signal(&sa, SIGQUIT);
}
