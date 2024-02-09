#include "../includes/headers/minishell.h"

int	call_process(t_ast_node *node, char ***env)
{
	int	ret;

	ret = ft_process(node, env);
	if (ret == 127)
	{
		ft_output_nl("syntax error", STDERR_FILENO);
		return (127);
	}
	return (ret);
}

// process a node
int	ft_process(t_ast_node *node, char ***env)
{
	if (!node)
		return (0);
	else if (node->type == NODE_LOGICAL)
		return (wich_logical(node, env));
	else if (node->type == NODE_PIPE)
		return (ft_pipe(node, env));
	else if (node->type == NODE_COMMAND)
		return (ft_run(node, env));
	else
		return (127);
}

int	wich_logical(t_ast_node *node, char ***env)
{
	if (ft_strcmp(node->value, "&&") == 0)
		return (ft_and(node, env));
	else if (ft_strcmp(node->value, "||") == 0)
		return (ft_or(node, env));
	else
		return (-1);
}

// processes right if left is valid
int	ft_and(t_ast_node *node, char ***env)
{
	if (!ft_process(node->left, env))
		return (ft_process(node->right, env));
	return (1);
}

// processes right if left is invalid

int	ft_or(t_ast_node *node, char ***env)
{
	if (ft_process(node->left, env))
		return (ft_process(node->right, env));
	return (0);
}

/*
int	wich_redirect(t_ast_node *node, char ***env)
{
	if (ft_strcmp(node->value, "<") == 0)
		return(ft_redirect_in(node, env));
	else if (ft_strcmp(node->value, ">") == 0)
		return(ft_redirect_out(node, env));
	else if (ft_strcmp(node->value, "<<") == 0)
		return(ft_read_del(node, env));
	else if (ft_strcmp(node->value, ">>") == 0)
		return(ft_append_out(node, env));
	else
		return (-1);
}

int	ft_redirect_out(t_ast_node *node, char ***env)
{
	int fd;
	fd = open(node->left->value , O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return(1);
	node->right->fd_out = fd;
	ft_process(node->right, env);
	write(fd, "", 1);
	close(fd);
	return(0);
}

int	ft_redirect_in(t_ast_node *node, char ***env)
{
	int fd;
	fd = open(node->left->value , O_RDONLY);
	if (fd == -1)
		return(1);
	node->right->fd_in = fd;
	ft_process(node->right, env);
	close(fd);
	return(0);
}

int	ft_append_out(t_ast_node *node, char ***env)
{
	int fd;
	fd = open(node->left->value , O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return(1);
	node->right->fd_out = fd;
	ft_process(node->right, env);
	write(fd, "", 1);
	close(fd);
	return(0);
}

int	ft_read_del(t_ast_node *node, char ***env)
{

}
*/