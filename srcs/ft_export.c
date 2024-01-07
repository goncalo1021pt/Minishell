#include "../includes/headers/minishell.h"

static void	print_export(char **env)
{
	int		i;

    i = 0;
    while (env && env[i] != NULL)
    {
        printf("declare -x %s\n", env[i]);
        i ++;
    }
}

char	*get_env_name(char *env)
{
	char	*aux;
	size_t	size;
	
	if (!env)
		return (NULL);
	size = 0;
	while (env[size] != '=')
	{
		if (env[size] == 0)
			return (NULL);
		size ++;
	}
	size ++;G
	aux = (char *)malloc(sizeof(char) * (size + 1));
	if (aux == NULL)
		return (NULL);
	aux[size] = '\0';
	while (size > 0)
	{
		aux[size - 1] = env[size - 1];
		size --;
	}
	return (aux);
}

int	ft_export(char ***env, char **args)
{
	size_t	i;
	char	*name;
	char	*aux;

	if (!args || !args[0])
		return (1);
	if (!args[1])
	{
		print_export(*env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		name = get_env_name(args[i]);
		aux = ft_strdup(args[i]);
		if (!aux)
			return (2);
		if (change_env(name, aux, env))
		{
			free(name);
			return (3);
		}
		free(name);
		i++;
	}
	return (0);
}