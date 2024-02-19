#include "../../includes/headers/minishell.h"

t_ast_node	*ast_new_node(void *c)
{
	t_ast_node	*node;
	t_parser	*content;

	content = c;
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	if (c)
	{
		node->type = content->type;
		node->value = ft_strdup(content->str);
	}
	else
	{
		node->value = NULL;
		node->type = NODE_UNKNOWN;
	}
	node->fd_in = STDIN_FILENO;
	node->fd_out = STDOUT_FILENO;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	add_full_right(t_ast_node *current, t_ast_node *node)
{
	if (!current)
		return ;
	if (!current->right)
		current->right = node;
	else
		add_full_right(current->right, node);
}

void	add_full_left(t_ast_node *current, t_ast_node *node)
{
	if (!current)
		return ;
	if (!current->left)
		current->left = node;
	else
		add_full_left(current->left, node);
}

void	ast_add_node(t_ast_node *current, t_ast_node *node, char dir)
{
	if (!node)
		return ;
	if (!current)
		current = node;
	else if (dir == 'l')
		current->left = node;
	else if (dir == 'r')
		current->right = node;
}

void	ast_free(t_ast_node *node)
{
	if (!node)
		return ;
	ast_free(node->left);
	ast_free(node->right);
	free(node->value);
	free(node);
}
