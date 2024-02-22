/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:46 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/22 17:55:23 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	ft_redirect_in(t_ast_node *node, char *fname)
{
	int	fd;

	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		perror(fname);
		return (1);
	}
	node->fd_in = fd;
	return (0);
}

int	ft_redirect_out(t_ast_node *node, char *fname)
{
	int	fd;

	if (node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(fname);
		return (1);
	}
	node->fd_out = fd;
	return (0);
}

int	ft_append_out(t_ast_node *node, char *fname)
{
	int	fd;

	if (node->fd_out != STDOUT_FILENO)
		close(node->fd_out);
	fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(fname);
		return (1);
	}
	node->fd_out = fd;
	return (0);
}

int	ft_recive_fd_in(t_ast_node *node, t_ast_node *c_node)
{
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	node->fd_in = c_node->fd_in;
	return (0);
}

int	ft_get_here_rec(t_ast_node *node)
{
	if (node && node->type == NODE_COMMAND)
	{
		return (ft_get_here(node));
	}
	else if (node)
	{
		return (ft_get_here_rec(node->left) + ft_get_here_rec(node->right));
	}
	return (0);
}
