/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:58 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/28 14:48:53 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

void	root_handler(int signal, siginfo_t *info, void *context)
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
}

void	here_handler(int signal, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signal == SIGINT)
	{
		ft_printf("\n");
		ft_exit(130);
	}
}

void	choose_signal(t_signal_time type)
{
	static struct sigaction	sa;

	if (type == ROOT)
	{
		sa.sa_sigaction = root_handler;
		sa.sa_flags = SA_SIGINFO;
		if (sigemptyset(&sa.sa_mask) != 0)
			return ;
		sigaction(SIGINT, &sa, NULL);
		ignore_signal(&sa, SIGQUIT);
	}
	else if (type == CHILD)
	{
		sa.sa_handler = SIG_DFL;
		sa.sa_flags = 0;
		if (sigemptyset(&sa.sa_mask) != 0)
			return ;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
	}
	else
		choose_signal2(type, sa);
}

void	choose_signal2(t_signal_time type, struct sigaction sa)
{
	if (type == HEREDOC)
	{
		sa.sa_sigaction = here_handler;
		sa.sa_flags = SA_SIGINFO;
		if (sigemptyset(&sa.sa_mask) != 0)
			return ;
		sigaction(SIGINT, &sa, NULL);
		ignore_signal(&sa, SIGQUIT);
	}
	else if (type == IGNORE)
	{
		ignore_signal(&sa, SIGINT);
		ignore_signal(&sa, SIGQUIT);
	}
}

void	ignore_signal(struct sigaction *sa, int signal)
{
	struct sigaction	original_sa;
	int					original_flags;

	original_flags = sa->sa_flags;
	sa->sa_handler = SIG_IGN;
	sa->sa_flags |= SA_SIGINFO;
	if (sigemptyset(&sa->sa_mask) != 0)
		return ;
	sigaction(signal, sa, &original_sa);
	sa->sa_flags = original_flags;
}
