#include "../includes/headers/minishell.h"

void    local_exec(char **args, char **env, int fd_in, int fd_out)
{
	if (access(args[0], F_OK) != 0)
	{
		ft_output(args[0], STDERR_FILENO);
		ft_output_nl(": No such file or directory", STDERR_FILENO);
		ft_exit(1);
	}
	if (set_fds(fd_in, fd_out) == -1 || execve(args[0], args, env) == -1)
	{
		perror(args[0]);
		ft_exit(errno);
	}
	close_fds(fd_in, fd_out);
	ft_exit(errno);
}
