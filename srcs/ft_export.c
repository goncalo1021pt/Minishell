#include "../includes/headers/minishell.h"

static void	print_export(char **env, int fd_out)
{
	int		i;

    i = 0;
    while (env && env[i] != NULL)
    {
		ft_output("declare -x ", fd_out);
        ft_output_export(env[i], fd_out);
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
			return (ft_strdup(env));
		size ++;
	}
	aux = (char *)malloc(sizeof(char) * (size + 1));
	if (aux == NULL)
		return (NULL);
	aux[size] = '\0';
	while (size > 0)
	{
		size --;
		aux[size] = env[size];
	}
	return (aux);
}

int	ft_export(char ***env, char **args, int fd_out)
{
	size_t	i;
	char	*name;
	char	*aux;

	if (!args || !args[0])
		return (1);
	if (!args[1])
	{
		print_export(*env, fd_out);
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
			free(aux);
			return (3);
		}
		free(name);
		i++;
	}
	return (0);
}
