#include "../includes/headers/minishell.h"

int	ft_env(char **env, char **args, int fd_out)
{
	int		i;

	i = 0;
	if (args[1])
		return (1);
	while (env && env[i] != NULL)
	{
		if (ft_strchr(env[i], '='))
			ft_output_nl(env[i], fd_out);
		i ++;
	}
	return (0);
}
