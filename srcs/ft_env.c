#include "../includes/headers/minishell.h"

int	ft_env(char **env, char **args)
{
	int		i;

    i = 0;
	if(args[1])
		return (1);
    while (env && env[i] != NULL)
    {
		if (ft_strchr(env[i], '='))
        	printf("%s\n", env[i]);
        i ++;
    }
	return (0);
}