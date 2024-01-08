#include "../includes/headers/minishell.h"

int    local_exec(char **args, char **env, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (2);
	else if (pid == 0)
	{
		if (set_fds(fd_in, fd_out) == -1 || execve(args[0], args, env) == -1)
		{
			perror(args[0]);
			exit(0);
		}
	}
	waitpid(pid, &status, 0);
    return (0);
}
