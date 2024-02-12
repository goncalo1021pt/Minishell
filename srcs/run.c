#include "../includes/headers/minishell.h"

char	**ft_get_args(t_ast_node *node)
{
	size_t		ac;
	size_t		i;
	t_ast_node	*aux;
	char		**args;

	ac = 0;
	aux = node;
	args = NULL;
	while (aux)
	{
		ac++;
		aux = aux->right;
	}
	if (my_alloc(sizeof(char *), ac + 1, (void **)(&args)))
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
	t_ast_node	*aux;

	aux = node->left;
	while (aux)
	{
		if (aux->type == NODE_REDIRECT_IN)
			return (ft_redirect_in(node, aux->value));
		else if (aux->type == NODE_REDIRECT_IN_HERE)
			return (ft_read_del(node, aux->value));
		else if (aux->type == NODE_REDIRECT_OUT)
			return (ft_redirect_out(node, aux->value));
		else if (aux->type == NODE_REDIRECT_OUT_APPENDS)
			return (ft_append_out(node, aux->value));
		aux = aux->left;
	}
	return (0);
}

static int	run_aux(t_ast_node *node, char **args, char ***env)
{
	if (!(node->value))
		return (0);
	else if ((node->value)[0] == '/' || (node->value)[0] == '.')
		return (local_exec(args, *env, node->fd_in, node->fd_out));
	else if (ft_strcmp(node->value, "echo") == 0)
		return (ft_echo(args, node->fd_out));
	else if (ft_strcmp(node->value, "cd") == 0)
		return (ft_cd(args, env));
	else if (ft_strcmp(node->value, "pwd") == 0)
		return (ft_pwd(node->fd_out));
	else if (ft_strcmp(node->value, "export") == 0)
		return (ft_export(env, args, node->fd_out));
	else if (ft_strcmp(node->value, "unset") == 0)
		return (ft_unset(env, args));
	else if (ft_strcmp(node->value, "env") == 0)
		return (ft_env(*env, args, node->fd_out));
	else if (ft_strcmp(node->value, "exit") == 0)
	{
		free(args);
		ft_exit(0);
		return (0);
	}
	else
		return (path_exec(args, *env, node->fd_in, node->fd_out));
}

int	ft_run(t_ast_node *node, char ***env)
{
	char	**args;
	int		ret;

	ret = 0;
	args = ft_get_args(node);
	ft_get_fds(node);
	ret = run_aux(node, args, env);
	free(args);
	return (ret);
}
