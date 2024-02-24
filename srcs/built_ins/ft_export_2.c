/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:23:27 by sergio            #+#    #+#             */
/*   Updated: 2024/02/24 16:16:55 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	check_add(char *arg, int *ret, char ***env)
{
	size_t	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			export_add(arg, env);
			return (1);
		}
		if (arg[i] == '+' || arg[i] == '=')
			break ;
		i++;
	}
	if (ste(arg, '+'))
	{
		ft_output("minishell: export: `", STDERR_FILENO);
		ft_output(arg, STDERR_FILENO);
		ft_output_nl("': not a valid identifier", STDERR_FILENO);
		*ret = 1;
		return (1);
	}
	return (0);
}

static char	*get_env_name_2(char *env, size_t *len)
{
	char	*aux;
	size_t	size;

	if (!env)
		return (NULL);
	size = 0;
	while (env[size] != '+')
		size++;
	aux = (char *)malloc(sizeof(char) * (size + 1));
	if (aux == NULL)
		return (NULL);
	aux[size] = '\0';
	*len = size;
	while (size > 0)
	{
		size--;
		aux[size] = env[size];
	}
	return (aux);
}

int	export_add(char *arg, char ***env)
{
	char	*name;
	char	*new_env;
	char	**envf;
	size_t	len;

	len = 0;
	name = get_env_name_2(arg, &len);
	if (!name)
		return (1);
	envf = get_env2(name, *env);
	if (envf)
		new_env = ft_strjoin(*envf, &(arg[len + 2]));
	else
		new_env = ft_strjoin(name, &(arg[len + 1]));
	if (!new_env)
	{
		free(name);
		return (1);
	}
	if (change_env(name, new_env, env))
		return (free(name), 1);
	free(name);
	return (0);
}
