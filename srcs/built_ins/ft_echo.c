/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:26:48 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/24 15:04:48 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

static void	echo_aux(char **arg, int fd_out)
{
	size_t	i;

	i = 1;
	while (arg[i])
	{
		ft_output(arg[i], fd_out);
		if (arg[i + 1])
			ft_output(" ", fd_out);
		i++;
	}
}

static t_bool	check_flag(char *str)
{
	size_t	i;

	if (str[0] == '-' && str[1] == 'n')
	{
		i = 2;
		while (str[i])
		{
			if (str[i] != 'n')
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

int	ft_echo(char **arg, int fd_out)
{
	if (check_flag(arg[1]))
	{
		echo_aux(&(arg[1]), fd_out);
	}
	else
	{
		echo_aux(arg, fd_out);
		ft_output_nl("", fd_out);
	}
	return (0);
}
