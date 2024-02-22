#include "../../includes/headers/minishell.h"

static void	print_export(char **env, int fd_out)
{
	int	i;

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

static void	invalid(char *arg)
{
	ft_output("minishell: export: `", STDERR_FILENO);
	ft_output(arg, STDERR_FILENO);
	ft_output_nl("': not a valid identifier", STDERR_FILENO);
}

static int	ft_export_aux(char ***env, char **args)
{
	size_t	i;
	char	*name;
	char	*aux;

	i = 0;
	while (args[++i])
	{
		if (args[i][0] == '=')
		{
			invalid(args[i]);
			continue ;
		}
		if (args[i][0] == '_' && args[i][1] == '=')
			continue ;
		name = get_env_name(args[i]);
		aux = ft_strdup(args[i]);
		if (!aux)
			return (1);
		if (change_env(name, aux, env))
			return (free(name), free(aux), 3);
		free(name);
	}
	return (0);
}

int	ft_export(char ***env, char **args, int fd_out)
{
	int	ret;

	ret = 0;
	if (!args || !args[0])
	{
		perror("minishell: ");
		return (errno);
	}
	if (!args[1])
	{
		print_export(*env, fd_out);
		return (0);
	}
	ret = ft_export_aux(env, args);
	return (ret);
}
