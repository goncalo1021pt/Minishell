#include "../includes/headers/minishell.h"

/*
returns the env variable corresponding to name (starting after name)
*/

char    *get_env(char *name, char **env)
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

/*
returns a pointer to the env variable corresponding to name
*/

char    **get_env2(char *name, char **env)
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

int	add_env(char *new_env, char ***env)
{
	char **aux;

	aux = ft_astr_extend(*env, new_env);
	if (aux)
	{
		free(*env);
		*env = aux;
		return(0);
	}
	else
		return(1);
}

int	change_env(char *name, char *new, char ***env)
{
    char    **where;

    where = get_env2(name, *env);
    if (where)
    {
        free(*where);
        *where = new;
		if (where)
			return (0);
		else
			return(1);
    }
    else
    {
        return (add_env(new, env));
    }
}

int	remove_env(char *name, char ***env)
{
	char 	**aux;
	size_t	out;

	out = 0;
	while(ft_strncmp(name, (*env)[out], ft_strlen(name)))
		out++;
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
