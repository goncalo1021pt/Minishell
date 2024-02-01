#include "../includes/headers/minishell.h"

static void	echo_aux(char **arg, int fd_out)
{
	size_t	i;

	i = 1;
	while (arg[i])
	{
		ft_output(arg[i], fd_out);
		if (arg[i + 1])
			ft_output(" ", fd_out);
		i++;
	}
}

int	ft_echo(char **arg, int fd_out)
{
	if (ft_strcmp(arg[1], "-n"))
	{
		echo_aux(arg, fd_out);
		ft_output_nl("", fd_out);
	}
	else
	{
		echo_aux(&(arg[1]), fd_out);
	}
	return (0);
}
