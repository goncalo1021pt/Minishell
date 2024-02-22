/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:03 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/22 13:46:45 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

static void	fuck_fds(void)
{
	size_t	fd;

	fd = 3;
	while (fd < FOPEN_MAX)
	{
		close(fd);
		fd++;
	}
}

void	ft_exit(int status)
{
	t_info	info;

	info = exit_info(NULL, NULL);
	if (*(info.tree))
		ast_free(*(info.tree));
	if (*(info.env))
		clean_arr_str(*(info.env));
	fuck_fds();
	ft_output_nl("exit", STDOUT_FILENO);
	exit(status);
}
static t_bool	ft_strisnum(char *str)
{
	size_t	count;

	count = 0;
	
	while (str[count])
	{
		if (!ft_isdigit(str[count]))
			return(FALSE);
		count++;
	}
	return (TRUE);
}


void	ft_ft_exit(char **args)
{
	int	ret;
	if (!args[1])
	{
		free(args);
		ft_exit(0);
	}
	if (!args[2])
	{
		if (!ft_strisnum(args[1]))
		{
			ft_output("minishell: exit: ", STDERR_FILENO);
			ft_output(args[1], STDERR_FILENO);
			ft_output_nl(": numeric argument required", STDERR_FILENO);
			ret = 2;
		}
		else
			ret = ft_atoi(args[1]);
		free(args);
		ft_exit(ret);
	}
	else
	{
		ft_output_nl("minishell: exit: too many arguments", STDERR_FILENO);
	}
}
