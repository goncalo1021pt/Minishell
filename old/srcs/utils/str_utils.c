#include "../../includes/headers/minishell.h"

void	clean_arr_str(char **astr)
{
	int	i;

	if (!astr || !*astr)
		return ;
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
	int	i;

	i = 0;
	while (astr && astr[i] != NULL)
	{
		ft_output_nl(astr[i], STDOUT_FILENO);
		i++;
	}
}

t_bool	is_in_array(char c, char *arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_arrlen(char **arr)
{
	int	ctd;

	ctd = 0;
	while (arr && arr[ctd])
		ctd++;
	return (ctd);
}

void	*free_arr_str(char **out, int ctd)
{
	while (ctd >= 0)
		free(out[ctd--]);
	free(out);
	return (NULL);
}
