#include "../../includes/headers/minishell.h"

void	print_tree(t_ast_node *node)
{
	if (node)
	{
		ft_printf("%i :: %s\n", node->type, node->value);
		ft_printf("\n%s LEFT\n", node->value);
		print_tree(node->left);
		ft_printf("\n%s RIGHT\n", node->value);
		print_tree(node->right);
	}
}
