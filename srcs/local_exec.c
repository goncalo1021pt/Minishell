#include "../includes/headers/minishell.h"

int    local_exec(char **args, char **env, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	if (access(args[0], F_OK) != 0)
	{
		ft_output(args[0], STDERR_FILENO);
		ft_output_nl(": No such file or directory", STDERR_FILENO);
		return(1);
	}
	set_signals_ignore();
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		set_signals_child();
		if (set_fds(fd_in, fd_out) == -1 || execve(args[0], args, env) == -1)
		{
			perror(args[0]);
			ft_exit(0);
		}
	}
	close_fds(fd_in, fd_out);
	waitpid(pid, &status, 0);
	set_signals_root();
	return (status);
}
