#include "../../includes/headers/minishell.h"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	char			**args;
	struct s_node	*next;
	struct s_node	*child;
}	t_node;

t_node	*new_node(t_node_type type, char **args)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = args;
	node->next = NULL;
	node->child = NULL;
	return (node);
}
