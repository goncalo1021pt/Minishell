#include "../../includes/headers/minishell.h"

void	ft_exit(int status)
{
	t_info	info;

	info = exit_info(NULL, NULL);
	if (*(info.tree))
		ast_free(*(info.tree));
	if (*(info.env))
		clean_arr_str(*(info.env));
	exit(status);
}
