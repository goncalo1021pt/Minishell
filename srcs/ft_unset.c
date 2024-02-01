#include "../includes/headers/minishell.h"

int	ft_unset(char ***env, char **args)
{
	size_t	i;

	if (!args || !args[0])
		return (1);
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (remove_env(args[i], env))
		{
			return (2);
		}
		i++;
	}
	return (0);
}
