#include "../includes/headers/minishell.h"

/*
returns the env variable corresponding to name (starting after name)
*/

char    *get_env(char *name, char **env)
{
    size_t	i;

	i = 0;
	while (env[i])
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
	while (env[i])
	{
		if (ft_strncmp(name, env[i], ft_strlen(name)) == 0)
			return (&env[i]);
		i++;
	}
	return (NULL);
}

// change_env incorrect

int	change_env(char *name, char *new, char ***env)
{
    char    **where;

    where = find_env2(name, *env);
    if (where)
    {
        free(*where);
        *where = ft_strjoin(name, new);
    }
    else
    {
        *env = ft_astr_extend(*env, new);
    }
}

int	add_env(char *new_env, char ***env)
{
	char **aux;

	aux = ft_astr_dup_add(char *env, char new_env);
	if (aux)
	{
		clean_astr(*env);
		*env = aux;
		return(0);
	}
	else
		return(1);
}