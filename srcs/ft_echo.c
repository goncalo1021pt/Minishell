#include "../includes/headers/minishell.h"

int	ft_echo(char **arg, int fd_out)
{
	size_t	i;

	i = 1;
	if (ft_strcmp(arg[1], "-n"))
	{
		i++;
		while (arg[i])
		{
			ft_output(arg[i], fd_out);
			if (arg[i + 1])
				ft_output(" ", fd_out);
			i++;
		}
		ft_output_nl("", fd_out);
	}
	else
	{
		while (arg[i])
		{
			ft_output(arg[i], fd_out);
			if (arg[i + 1])
				ft_output(" ", fd_out);
			i++;
		}
	}
	return (0);
}