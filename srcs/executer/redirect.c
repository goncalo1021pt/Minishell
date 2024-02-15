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

static int	del_eof(int pip)
{
	close(pip);
	ft_output("minishell: warning: ", STDOUT_FILENO);
	ft_output("here-document ", STDOUT_FILENO);
	ft_output_nl("delimited by end-of-file", STDOUT_FILENO);
	return (errno);
}

int	ft_read_del(t_ast_node *node, char *fname)
{
	char	*line;
	int		pip[2];

	choose_signal(HEREDOC);
	if (pipe(pip) == -1)
		return (1);
	if (node->fd_in != STDIN_FILENO)
		close(node->fd_in);
	line = readline("> ");
	if (!line)
		ft_exit(del_eof(pip[1]));
	while (ft_strncmp(line, fname, ft_strlen(line)) != 0)
	{
		write(pip[1], line, ft_strlen(line));
		free(line);
		line = readline("> ");
		if (!line)
			ft_exit(del_eof(pip[1]));
	}
	free(line);
	write(pip[1], "\n", 1);
	close(pip[1]);
	node->fd_in = pip[0];
	choose_signal(CHILD);
	return (0);
}
