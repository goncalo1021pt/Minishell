#include "../includes/headers/minishell.h"

t_bool check_expander(char *str)
{
	int ctd;

	ctd = 0;
	while (str[ctd])
	{
		if (str[ctd] == '$')
			ctd++;
	}
	return (FALSE);
}