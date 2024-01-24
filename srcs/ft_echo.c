#include "../includes/headers/minishell.h"

int	ft_env(char **env, char **args, int fd_out)
{
	size_t	i;

	i = 1;
	if (!ft_strcmp(arg[1], "-n"))
	{
		i++;
		while (arg[i])
		{
			ft_output(arg[i], fd_out);
			ft_output_nl("", fd_out);
			i++;
		}
	}
	else
	{
		while (arg[i])
		{
			ft_output_nl(arg[i], fd_out);
			i++;
		}
	}
}