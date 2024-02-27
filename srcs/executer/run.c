/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:51 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/27 15:46:48 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

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
		if (aux->value)
			ac++;
		aux = aux->right;
	}
	if (my_alloc(sizeof(char *), ac + 1, (void **)(&args)))
		return (NULL);
	i = 0;
	aux = node;
	while (i < ac)
	{
		if (aux->value)
			args[i++] = aux->value;
		aux = aux->right;
	}
	return (args);
}

int	close_astr_fds(t_ast_node *aux, int ret)
{
	while (aux)
	{
		close_fds(aux->fd_in, aux->fd_out);
		aux = aux->left;
	}
	return (ret);
}

int	ft_get_fds(t_ast_node *node)
{
	t_ast_node	*aux;
	int			ret;

	ret = 0;
	aux = node->left;
	while (aux)
	{
		printf("val:%s$\n", aux->value);
		if (aux->type == NODE_REDIRECT_IN)
			ret = ft_redirect_in(node, aux->value);
		else if (aux->type == NODE_REDIRECT_IN_HERE)
			ret = ft_recive_fd_in(node, aux);
		else if (aux->type == NODE_REDIRECT_OUT)
			ret = ft_redirect_out(node, aux->value);
		else if (aux->type == NODE_REDIRECT_OUT_APPENDS)
			ret = ft_append_out(node, aux->value);
		else if (aux->type == NODE_REDIRECT_AMB)
			ret = ft_read_amb(aux->value);
		if (ret)
			return (close_astr_fds(aux, ret));
		aux = aux->left;
	}
	return (ret);
}

static int	run_aux(t_ast_node *node, char **args, char ***env)
{
	if (!(node->value))
		return (0);
	else if ((node->value)[0] == '/' || (node->value)[0] == '.')
		return (local_exec(args, *env, node->fd_in, node->fd_out));
	else if (ft_strcmp(node->value, "echo") == 0)
		ft_echo(args, node->fd_out);
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
		ft_ft_exit(args);
		return (1);
	}
	else
		return (path_exec(args, *env, node->fd_in, node->fd_out));
	return (0);
}

int	ft_run(t_ast_node *node, char ***env)
{
	char	**args;
	int		ret;

	ret = 1;
	if (!ft_get_fds(node))
	{
		args = ft_get_args(node);
		ret = run_aux(node, args, env);
		free(args);
	}
	close_fds(node->fd_in, node->fd_out);
	return (ret);
}
