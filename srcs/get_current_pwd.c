#include "../includes/headers/minishell.h"

char	*get_current_pwd()
{
	char	buffer[MAX_PATH_SIZE];
	char	*ret;
	int		i;

	i = 0;
	while (i < size)
	{
		buffer[i] = 0;
		i ++;
	}
	getcwd(buffer, MAX_PATH_SIZE);
	ret = ft_strdup(buffer);
	return (ret);
}