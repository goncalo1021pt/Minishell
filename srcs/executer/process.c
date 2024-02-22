/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:43 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/21 19:26:08 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	call_process(t_ast_node *node, char ***env)
{
	int	ret;

	if (ft_get_here_rec(node))
		return (1);
	ret = ft_process(node, env);
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
		return (2);
}

int	wich_logical(t_ast_node *node, char ***env)
{
	if (ft_strcmp(node->value, "&&") == 0)
		return (ft_and(node, env));
	else if (ft_strcmp(node->value, "||") == 0)
		return (ft_or(node, env));
	else
		return (2);
}

// processes right if left is valid
int	ft_and(t_ast_node *node, char ***env)
{
	int	ret;

	ret = ft_process(node->left, env);
	if (!ret)
		return (ft_process(node->right, env));
	return (ret);
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