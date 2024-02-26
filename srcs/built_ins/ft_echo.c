/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:26:48 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/26 15:21:43 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

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

static void	echo_aux(char **arg, int fd_out, int check)
{
	size_t	i;
	
	i = 1;
	while (arg[i])
	{
		if(check > 0 || !check_flag(arg[i]))
		{
			check = 1;
			ft_output(arg[i], fd_out);
			if (arg[i + 1])
				ft_output(" ", fd_out);
		}
		i++;
	}
}

int	ft_echo(char **arg, int fd_out)
{
	if (check_flag(arg[1]))
	{
		echo_aux(&(arg[1]), fd_out, 0);
	}
	else
	{
		echo_aux(arg, fd_out, 1);
		ft_output_nl("", fd_out);
	}
	return (0);
}
