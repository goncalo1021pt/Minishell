#include "../../includes/headers/minishell.h"

void	ft_exit(int status)
{
	t_info	info;

	info = exit_info(NULL, NULL);
	ast_free(*(info.tree));
	clean_arr_str(*(info.env));
	exit(status);
}
