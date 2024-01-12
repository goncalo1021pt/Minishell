#include "../includes/headers/minishell.h"

int	set_fd_in(int fd_in)
{
	int	ret;

	(void)ret;
	if (fd_in == STDIN_FILENO)
		return (0);
	ret = dup2(fd_in, STDIN_FILENO);
	return (0);
}

int	set_fd_out(int fd_out)
{
	int	ret;

	if (fd_out == STDOUT_FILENO)
		return (0);
	ret = dup2(fd_out, STDOUT_FILENO);
	return (ret);
}

int	set_fds(int fd_in, int fd_out)
{
	int	ra;
	int	rb;

	ra = set_fd_in(fd_in);
	rb = set_fd_out(fd_out);
	if (ra == -1 || rb == -1)
		return(-1);
	else
		return (0);
}
