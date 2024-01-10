#include "../includes/headers/minishell.h"

t_ast_node	*ast_create_node(t_node_type type, char *value)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	ast_free(t_ast_node *node)
{
	if (!node)
		return ;
	ast_free(node->left);
	ast_free(node->right);
	free(node);
}

const char	*nodeTypeToString(t_node_type type)
{
	
	if (type == NODE_COMMAND) 
		return ("NODE_COMMAND");
	else if (type == NODE_ARGUMENT)
		return ("NODE_ARGUMENT");
	else if (type == NODE_PIPE)
		return ("NODE_PIPE");
	else if (type == NODE_REDIRECT)
		return ("NODE_REDIRECT");
	else
		return ("NODE_UNKNOWN");
}

void	ast_print(t_ast_node *node)
{
	if (!node)
		return ;
	printf("type: %s, value: %s\n", nodeTypeToString(node->type), node->value);
	ast_print(node->left);
	ast_print(node->right);
}

void	ast_add_node(t_ast_node *root, t_ast_node *node)
{
	if (!root || !node)
		return ;
	if (!root->left)
		root->left = node;
	else if (!root->right)
		root->right = node;
	else
		ast_add_node(root->right, node);
}

// int	main(void)
// {
// 	t_ast_node *root;
// 	t_ast_node *node;

// 	root = ast_create_node(NODE_COMMAND, "echo");
// 	node = ast_create_node(NODE_ARGUMENT, "hello");
// 	ast_add_node(root, node);
// 	node = ast_create_node(NODE_ARGUMENT, "world");
// 	ast_add_node(root, node);
// 	node = ast_create_node(NODE_PIPE, "|");
// 	ast_add_node(root, node);
// 	node = ast_create_node(NODE_COMMAND, "wc");
// 	ast_add_node(root, node);
// 	node = ast_create_node(NODE_REDIRECT, ">");
// 	ast_add_node(root, node);
// 	node = ast_create_node(NODE_ARGUMENT, "file.txt");
// 	ast_add_node(root, node);
// 	ast_print(root);
// 	ast_free(root);
// 	return (0);
// }
