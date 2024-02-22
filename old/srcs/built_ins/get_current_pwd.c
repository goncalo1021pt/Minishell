#include "../../includes/headers/minishell.h"

char	*get_current_pwd(void)
{
	char	buffer[MAX_PATH_SIZE];
	char	*ret;
	int		i;

	i = 0;
	while (i < MAX_PATH_SIZE)
	{
		buffer[i] = 0;
		i ++;
	}
	getcwd(buffer, MAX_PATH_SIZE);
	ret = ft_strdup(buffer);
	return (ret);
}
