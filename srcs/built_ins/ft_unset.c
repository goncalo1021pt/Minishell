/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:11 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/22 13:56:01 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	ft_unset(char ***env, char **args)
{
	size_t	i;

	if (!args || !args[0])
		return (1);
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (remove_env(args[i], env))
		{
			return (0);
		}
		i++;
	}
	return (0);
}
