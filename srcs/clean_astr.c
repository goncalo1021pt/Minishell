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

void	print_astr(char **astr)
{
	int		i;

	i = 0;
	while (astr && astr[i] != NULL)
	{
		ft_output_nl(astr[i], STDOUT_FILENO);
		i ++;
	}
}
