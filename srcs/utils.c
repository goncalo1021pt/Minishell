#include "../includes/headers/minishell.h"

t_bool is_in_array(char c, char *arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (arr[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
