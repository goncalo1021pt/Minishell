#include "../includes/headers/minishell.h"

void	sigint_handeler_root(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigint_handeler_child(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		kill(getpid(), SIGINT);
	}
}

void	sigquit_handler_child(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_printf("Quit\n");
		kill(getpid(), SIGQUIT);
	}
}
void	sigint_handeler_here(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		ft_exit(-1);
	}
}
void	sigquit_handler_here(int signal)
{
	if (signal == SIGQUIT)
	{
		ft_printf("Quit\n");
		ft_exit(-1);
	}
}
void	set_signals_root(void)
{
	signal(SIGINT, sigint_handeler_root);
	signal(SIGQUIT, SIG_IGN);
}

void	set_signals_child(void)
{
	signal(SIGINT, sigint_handeler_child);
	signal(SIGQUIT, sigquit_handler_child);
}

void	set_signals_here(void)
{
	signal(SIGINT, sigint_handeler_here);
	signal(SIGQUIT, sigquit_handler_here);
}
void	set_signals_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
