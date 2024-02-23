/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:26:41 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/22 14:19:35 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	add_env(char *new_env, char ***env)
{
	char	**aux;

	aux = ft_astr_extend(*env, new_env);
	if (aux)
	{
		free(*env);
		*env = aux;
		return (0);
	}
	else
		return (1);
}

int	change_env(char *name, char *new, char ***env)
{
	char	**where;

	if (!name && !strchr(new, '='))
		return (add_env(new, env));
	where = get_env2(name, *env);
	if (where)
	{
		if (!strchr(new, '=') && strchr(*where, '='))
			return (0);
		free(*where);
		*where = new;
		if (where)
			return (0);
		else
			return (1);
	}
	else
	{
		return (add_env(new, env));
	}
}

static int	remove_env_aux(char **aux, char ***env, size_t out)
{
	if (aux)
	{
		free((*env)[out]);
		free(*env);
		*env = aux;
		return (0);
	}
	else
		return (1);
}

int	remove_env(char *name, char ***env)
{
	char	**aux;
	char	*name_e;
	size_t	out;

	out = 0;
	if (!env || !(*env) || !(*env)[out])
		return (0);
	name_e = ft_strjoin(name, "=");
	while (ft_strcmp(name, (*env)[out]) &&
		ft_strncmp(name_e, (*env)[out], ft_strlen(name_e)))
	{
		if ((*env)[out] == NULL)
		{
			free(name_e);
			return (0);
		}
		out++;
	}
	free(name_e);
	aux = ft_astr_reduce(*env, out);
	return (remove_env_aux(aux, env, out));
}
