#include "../includes/headers/minishell.h"

int	ft_pwd(char **env)
{
	char	*pwd;

	pwd = get_current_pwd();
	if(!pwd)
		return(0);
	printf("%s\n",pwd);
	free(pwd);
	return(0);
}