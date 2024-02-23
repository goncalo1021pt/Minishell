/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:41 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/22 15:22:56 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

static int	pipe_2(t_ast_node *node, char ***env, int pip[2], int fk1)
{
	int		fk2;
	int		status;

	fk2 = fork();
	if (fk2 < 0)
	{
		perror("minishell: ");
		ft_exit(errno);
	}
	if (fk2 == 0)
	{
		close(pip[1]);
		status = ft_process(node->right, env);
		ft_exit(status);
	}
	close(pip[1]);
	close(pip[0]);
	waitpid(fk1, NULL, 0);
	waitpid(fk2, &status, 0);
	status = error_handler(status);
	return (status);
}

int	ft_pipe(t_ast_node *node, char ***env)
{
	int		pip[2];
	int		fk1;

	if (pipe(pip) == -1)
	{
<<<<<<< HEAD:srcs/pipe.c
		perror("minishell: ");
=======
		perror("minishell:");
>>>>>>> refs/remotes/origin/main:srcs/executer/pipe.c
		return (errno);
	}
	node->left->fd_out = pip[1];
	node->left->fd_in = node->fd_in;
	node->right->fd_in = pip[0];
	node->right->fd_out = node->fd_out;
	fk1 = fork();
	if (fk1 < 0)
	{
<<<<<<< HEAD:srcs/pipe.c
		perror("fork");
		ft_exit (errno);
=======
		perror("minishell:");
		ft_exit(errno);
>>>>>>> refs/remotes/origin/main:srcs/executer/pipe.c
	}
	if (fk1 == 0)
	{
		close(pip[0]);
<<<<<<< HEAD:srcs/pipe.c
		ft_process(node->left, env);
		ft_exit(0);
=======
		ft_exit(ft_process(node->left, env));
>>>>>>> refs/remotes/origin/main:srcs/executer/pipe.c
	}
	return (pipe_2(node, env, pip, fk1));
}
