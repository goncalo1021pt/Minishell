#include "../includes/headers/minishell.h"

// t_ast_node	*ast_new_node(t_node_type type, char *value)
// {
// 	t_ast_node	*node;

// 	node = malloc(sizeof(t_ast_node));
// 	if (!node)
// 		return (NULL);
// 	node->type = type;
// 	node->value = ft_strdup(value);
// 	node->fd_in = STDIN_FILENO;
// 	node->fd_out = STDOUT_FILENO;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

t_ast_node	*ast_new_node(void* c)
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

void add_full_right(t_ast_node *current, t_ast_node *node)
{
	if (!current)
		return ;
	if (!current->right)
		current->right = node;
	else
		add_full_right(current->right, node);
}

void add_full_left(t_ast_node *current, t_ast_node *node)
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
	else if(dir == 'r')
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

const char	*nodeTypeToString(t_node_type type)
{
	if (type == NODE_COMMAND) 
		return ("NODE_COMMAND");
	else if (type == NODE_PIPE)
		return ("NODE_PIPE");
	else if (type == NODE_REDIRECT_IN_HERE)
		return ("NODE_REDIRECT IN HERE");
	else if (type == NODE_REDIRECT_IN)
		return ("NODE_REDIRECT IN");
	else if (type == NODE_REDIRECT_OUT)
		return ("NODE_REDIRECT OUT");
	else if (type == NODE_REDIRECT_OUT_APPENDS)
		return ("NODE_REDIRECT OUT APPENDS");
	else if (type == NODE_LOGICAL)
		return ("NODE_LOGICAL");
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
