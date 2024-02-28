/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:48 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/28 14:37:37 by sergmigu         ###   ########.fr       */
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

static void	write_expander(char *line, int fd_out, int mode)
{
	char	*aux;
	char	*aux2;

	if (!line)
		return ;
	if (mode == 1)
	{
		aux2 = ft_strdup(line);
		aux = expander(aux2, *exit_info(NULL, NULL).env);
		write(fd_out, aux, ft_strlen(aux));
		if (aux)
			free(aux);
	}
	else
		write(fd_out, line, ft_strlen(line));
}

static void	ft_read_del_aux(int fd_out, char *fname, int mode)
{
	char	*line;

	choose_signal(HEREDOC);
	line = readline("> ");
	if (!line)
	{
		free_hd(fname, mode);
		ft_exit(del_eof(fd_out));
	}
	while (ft_strcmp(line, fname) != 0)
	{
		write_expander(line, fd_out, mode);
		write(fd_out, "\n", 1);
		free(line);
		line = readline("> ");
		if (!line)
		{
			free_hd(fname, mode);
			ft_exit(del_eof(fd_out));
		}
	}
	free_hd(fname, mode);
	free(line);
	close(fd_out);
	ft_exit(0);
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
		if (ft_strchr(fname, '\'') || ft_strchr(fname, '\"'))
			ft_read_del_aux(pip[1], remove_quotes(ft_strdup(fname)), 0);
		else
			ft_read_del_aux(pip[1], fname, 1);
	}
	close(pip[1]);
	waitpid(fk, &status, 0);
	node->fd_in = pip[0];
	return (status);
}
