#include "../includes/headers/minishell.h"
/*

char	*get_env(char *name, char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(name, env[i], ft_strlen(name)) == 0)
			return (&(env[i][ft_strlen(name)]));
		i++;
	}
	return (NULL);
}

char	**get_env2(char *name, char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(name, env[i], ft_strlen(name)) == 0)
			return (&env[i]);
		i++;
	}
	return (NULL);
}
*/

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

	if (!name && !strchr(new ,'='))
		return (add_env(new, env));
	where = get_env2(name, *env);
	if (where)
	{
		if(!strchr(new,'=') && strchr(*where,'='))
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

int	remove_env(char *name, char ***env)
{
	char	**aux;
	char	*name_e;
	size_t	out;

	out = 0;
	name_e = ft_strjoin(name, "=");
	if (!env || !(*env) || !(*env)[out])
		return (0);
	while (ft_strcmp(name, (*env)[out]) && ft_strncmp(name_e, (*env)[out], ft_strlen(name_e)))
	{
		if ((*env)[out] == NULL)
		{
			free(name_e);
			return(0);
		}
		out++;
	}
	free(name_e);
	aux = ft_astr_reduce(*env, out);
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
