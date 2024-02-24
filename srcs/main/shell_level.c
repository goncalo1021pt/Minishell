/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_level.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: goncalo1021pt <goncalo1021pt@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:32 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/24 21:59:54 by goncalo1021      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

static char	*inc_str(char *i)
{
	if (!i)
		return (ft_itoa(1));
	else
		return (ft_itoa(ft_atoi(i) + 1));
}

void	shell_level(char ***env)
{
	char	*lvl;

	lvl = get_env("SHLVL", *env);
	change_env("SHLVL", ft_strjoin_f2("SHLVL=", inc_str(lvl)), env);
}
