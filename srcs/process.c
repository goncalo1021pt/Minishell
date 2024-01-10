#include "../includes/headers/minishell.h"

// process a node

int	ft_process(t_ast_node *node, char ***env)
{
	if (node->type == NODE_COMMAND)
		return(ft_run(node, env));
	else if (node->type == NODE_PIPE)
		return (ft_pipe(node, env));
	else if (node->type == NODE_REDIRECT)
		return (wich_redirect(node, env));
	else if (node->type == NODE_ARGUMENT)
		return (0);
	else if (node->type == NODE_UNKNOWN)
		return (-1);
}

//runs a program or a built in

int	ft_run(t_ast_node *node, char ***env)
{

	if ((node->value)[0] == '/' || (node->value)[0] == '.')
		return(local_exec(node->args, env,node->fd_in, node->fd_out));
	else if (ft_strcmp(node->value, "echo") == 0)
		return(ft_echo());
	else if (ft_strcmp(node->value, "cd") == 0)
		return(ft_cd(node->args, env));
	

}

//forka o programa com um pipe

int	ft_pipe(t_ast_node *node, char ***env)
{
	int		pip[2];
	int		fk1;
	int		fk2;
	int		status1;
	int		status2;

	if (pipe(pip) == -1)
	{
		perror("pipe");
		return(1);
	}
	node->left->fd_out = pip[1];
	node->left->fd_in = node->fd_in;
	node->right->fd_in = pip[0];
	node->right->fd_out = node->fd_out;
	fk1 = fork();
	if (fk1 < 0)
	{
		perror("fork");
		return (2);
	}
	if (fk1 == 0)
	{
		ft_process(node->left, env);
		write(pip[1], "", 1);
		exit();
	}
	fk2 = fork();
	if (fk2 < 0)
	{
		perror("fork");
		return (2);
	}
	if (fk2 == 0)
	{
		status = ft_process(node->right, env);
		exit(status);
	}
	waitpid(fk1, NULL, 0);
	waitpid(fk2, &status, 0);
	close(pip[1]);
	close(pip[0]);
	return(status);
}

// processes right if left is valid
int	ft_and(t_ast_node *node, char ***env)
{
	if (!process(node->left, env))
		return(process(node->right, env))
	return(-1);
}

// processes right if left is invalid

int	ft_or(t_ast_node *node, char ***env)
{
	if (process(node->left, env))
		return(process(node->right, env))
	return(0);
}

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
