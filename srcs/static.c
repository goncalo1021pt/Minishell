#include "../includes/headers/minishell.h"

t_info	*exit_info(char ***env, t_ast_node **tree)
{
	static	info;

	if(env)
		info.env = env;
	if (tree)
		info.tree = tree;
	return (info);
}
