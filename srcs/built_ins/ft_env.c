/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:26:51 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:04 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	ft_env(char **env, char **args, int fd_out)
{
	int		i;

	i = 0;
	if (args && args[0] && args[1])
		return (1);
	while (env && env[i] != NULL)
	{
		if (ft_strchr(env[i], '='))
			ft_output_nl(env[i], fd_out);
		i ++;
	}
	return (0);
}
