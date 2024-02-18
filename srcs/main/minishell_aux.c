#include "../../includes/headers/minishell.h"

t_bool has_argument(char *str)
{
	int ctd;

	ctd = -1;
	while (str[++ctd])
		if (!is_in_array(str[ctd], SPACE_LIST))
			return (FALSE);
	return (TRUE);
}
