#include "../includes/headers/minishell.h"

void	clean_astr(char **astr)
{
	int	i;

	i = 0;
	while (astr[i])
	{
		free(astr[i]);
		i++;
	}
	free(astr);
}
