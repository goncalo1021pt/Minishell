#include "../includes/headers/minishell.h"

t_info	exit_info(char ***env, t_ast_node **tree)
{
	static t_info	info;

	if(env)
		info.env = env;
	if (tree)
		info.tree = tree;
	return (info);
}
