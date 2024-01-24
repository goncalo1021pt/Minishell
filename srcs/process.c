#include "../includes/headers/minishell.h"

int	call_process(t_ast_node *node, char ***env)
{
	int	ret;

	ret = ft_process(node, env);
	if (ret == -1)
	{
		ft_output_nl("syntax error", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

// process a node

int	ft_process(t_ast_node *node, char ***env)
{
	if (!node)
		return (0);
	else if (node->type == NODE_LOGICAL)
		return(wich_logical(node, env));
	else if (node->type == NODE_PIPE)
		return (ft_pipe(node, env));
	else if (node->type == NODE_COMMAND)
		return(ft_run(node, env));
	else
		return (-1);
}

char	**ft_get_args(t_ast_node *node)
{
	size_t		ac;
	size_t		i;
	t_ast_node	*aux;
	char		**args;

	ac = 0;
	aux = node;
	while (aux)
	{
		ac++;
		aux = aux->right;
	}
	if (my_alloc(sizeof(char *), ac + 1, args))
		return (NULL);
	i = 0;
	aux = node;
	while (i < ac)
	{
		args[i] = aux->value;
		i ++;
		aux = aux->right;
	}
	return (args);
}

int	ft_get_fds(t_ast_node *node)
{
	t_ast_node *aux;

	aux = node->left;
	while (aux)
	{
		if (aux->type == NODE_REDIRECT_IN)
			if (ft_redirect_in(node, aux->value))
				return (1);
		else if (aux->type == NODE_REDIRECT_IN_HERE)
			if (ft_read_del(node, aux->value))
				return (1);
		else if (aux->type == NODE_REDIRECT_OUT)
			if (ft_redirect_out(node, aux->value))
				return (1);
		else if (aux->type == NODE_REDIRECT_OUT_APPENDS)
			if (ft_append_out(node, aux->value))
				return (1);
		aux = aux->left;
	}
	return (0);
}

int	ft_redirect_in(t_ast_node *node, char *fname)
{
	int fd;

	close(node->fd_in);
	fd = open(fname , O_RDONLY);
	if (fd == -1)
	{
		perror(fname);
		return(1);
	}
	node->fd_in = fd;
	return(0);
}

int	ft_redirect_out(t_ast_node *node, char *fname)
{
	int fd;

	close(node->fd_out);
	fd = open(node->left->value , O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(fname);
		return(1);
	}
	node->fd_out = fd;
	return(0);
}

int	ft_append_out(t_ast_node *node, char *fname)
{
	int fd;

	close(node->fd_out);
	fd = open(node->left->value , O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(fname);
		return(1);
	}
	node->fd_out = fd;
	return(0);
}

int	ft_read_del(t_ast_node *node, char *fname)
{

}

//runs a program or a built in

int	ft_run(t_ast_node *node, char ***env)
{
	char	**args;
	int		ret;

	args = ft_get_args(node);
	ft_get_fds(node);
	if ((node->value)[0] == '/' || (node->value)[0] == '.')
		ret = local_exec(args, *env, node->fd_in, node->fd_out);
	else if (ft_strcmp(node->value, "echo") == 0)
		ret = ft_echo();
	else if (ft_strcmp(node->value, "cd") == 0)
		ret = ft_cd(args, env);
	else if (ft_strcmp(node->value, "pwd") == 0)
		ret = ft_pwd(node->fd_out);
	else if (ft_strcmp(node->value, "export") == 0)
		ret = ft_export(env, args, node->fd_out);
	else if (ft_strcmp(node->value, "unset") == 0)
		ret = ft_unset(env, args);
	else if (ft_strcmp(node->value, "env") == 0)
		ret = ft_env(*env, args, node->fd_out);
	else if (ft_strcmp(node->value, "ft_exit") == 0)
		ret = ft_ft_exit();
	else
		ret = path_exec(args, *env, node->fd_in, node->fd_out);
	free(args);
	close(node->fd_in);
	close(node->fd_out);
	return (ret);
}

//forka o programa com um pipe

int	ft_pipe(t_ast_node *node, char ***env)
{
	int		pip[2];
	int		fk1;
	int		fk2;
	int		status;

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
		ft_exit (2);
	}
	if (fk1 == 0)
	{
		ft_process(node->left, env);
		write(pip[1], "", 1);
		ft_exit(3);
	}
	fk2 = fork();
	if (fk2 < 0)
	{
		perror("fork");
		ft_exit (4);
	}
	if (fk2 == 0)
		ft_exit(ft_process(node->right, env));
	waitpid(fk1, NULL, 0);
	waitpid(fk2, &status, 0);
	close(pip[1]);
	close(pip[0]);
	return(status);
}

int	wich_logical(t_ast_node *node, char ***env)
{
	if (ft_strcmp(node->value, "&&") == 0)
		return(ft_and(node, env));
	else if (ft_strcmp(node->value, "||") == 0)
		return(ft_or(node, env));
	else
		return (-1);
}

// processes right if left is valid
int	ft_and(t_ast_node *node, char ***env)
{
	if (!process(node->left, env))
		return(process(node->right, env));
	return(1);
}

// processes right if left is invalid

int	ft_or(t_ast_node *node, char ***env)
{
	if (process(node->left, env))
		return(process(node->right, env));
	return(0);
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