/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:48 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/21 19:26:31 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

static void	exit_aux(void)
{
	perror("minishel: ");
	ft_exit(errno);
}

static int	del_eof(int pip)
{
	close(pip);
	ft_output("minishell: warning: ", STDOUT_FILENO);
	ft_output("here-document ", STDOUT_FILENO);
	ft_output_nl("delimited by end-of-file", STDOUT_FILENO);
	return (errno);
}

static int	ft_read_del_aux(int fd_out, char *fname)
{
	char	*line;

	choose_signal(HEREDOC);
	line = readline("> ");
	if (!line)
		return (del_eof(fd_out));
	while (ft_strcmp(line, fname) != 0)
	{
		write(fd_out, line, ft_strlen(line));
		write(fd_out, "\n", 1);
		free(line);
		line = readline("> ");
		if (!line)
			ft_exit(del_eof(fd_out));
	}
	free(line);
	close(fd_out);
	return (0);
}

int	ft_read_del(t_ast_node *node, char *fname)
{
	int		pip[2];
	int		status;
	pid_t	fk;

	if (pipe(pip) == -1)
		exit_aux();
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	choose_signal(IGNORE);
	fk = fork();
	if (fk < 0)
		exit_aux();
	if (fk == 0)
	{
		close(pip[0]);
		ft_exit(ft_read_del_aux(pip[1], fname));
	}
	close(pip[1]);
	waitpid(fk, &status, 0);
	node->fd_in = pip[0];
	return (status);
}

int	ft_get_here(t_ast_node *node)
{
	t_ast_node	*aux;
	int			ret;

	ret = 0;
	aux = node->left;
	while (aux)
	{
		if (aux->type == NODE_REDIRECT_IN_HERE)
			ret = ft_read_del(aux, aux->value);
		if (ret)
			return (ret);
		aux = aux->left;
	}
	return (ret);
}
