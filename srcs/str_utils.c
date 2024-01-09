#include "../includes/headers/minishell.h"

void	clean_arr_str(char **astr)
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

void	print_arr_str(char **astr)
{
	int		i;

	i = 0;
	while (astr && astr[i] != NULL)
	{
		ft_printf("%s\n", astr[i]);
		i ++;
	}
}
