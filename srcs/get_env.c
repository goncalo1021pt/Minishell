#include "../includes/headers/minishell.h"

/*
returns the env variable corresponding to name (starting after name)
*/

char	*get_env(char *name, char **env)
{
	size_t	i;
	char	*name_e;

	name_e = ft_strjoin(name, "=");
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(name_e, env[i], ft_strlen(name_e)) == 0)
		{
			free(name_e);
			return (&(env[i][ft_strlen(name_e)]));
		}
		else if (ft_strcmp(name, env[i]) == 0)
		{
			free(name_e);
			return (&(env[i][0]));
		}
		i++;
	}
	free (name_e);
	return (NULL);
}

/*
returns a pointer to the env variable corresponding to name
*/

char	**get_env2(char *name, char **env)
{
	size_t	i;
	char	*name_e;

	name_e = ft_strjoin(name, "=");
	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(name_e, env[i], ft_strlen(name_e)) == 0)
		{
			free(name_e);
			return (&env[i]);
		}
		else if (ft_strcmp(name, env[i]) == 0)
		{
			free(name_e);
			return (&env[i]);
		}
		i++;
	}
	return (NULL);
}