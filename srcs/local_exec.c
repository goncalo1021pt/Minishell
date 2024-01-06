#include "../includes/headers/minishell.h"

int    local_exec(char **args, char **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (2);
	else if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror(args[0]);
			exit(0);
		}
	}
	waitpid(pid, &status, 0);
    return (0);
}