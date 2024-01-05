#include "../includes/headers/minishell.h"

int	ft_unset(char ***env, char **args)
{
	char	*name;
	size_t	i;

	if (!args || !args[0])
		return (1);
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		name = get_env_name(args[i]);
		if (remove_env(name, env))
		{
			free(name);
			return (2);
		}
		free(name);
		i++;
	}
	return (0);
}