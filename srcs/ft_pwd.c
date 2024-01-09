#include "../includes/headers/minishell.h"

int	ft_pwd(int fd_out)
{
	char	*pwd;

	pwd = get_current_pwd();
	if(!pwd)
		return(0);
	ft_output_nl(pwd, fd_out);
	free(pwd);
	return(0);
}
