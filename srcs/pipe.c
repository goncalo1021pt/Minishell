#include "../includes/headers/minishell.h"

static int	pipe_2(t_ast_node *node, char ***env, int pip[2], int fk1)
{
	int		fk2;
	int		status;

	fk2 = fork();
	if (fk2 < 0)
	{
		perror("fork");
		ft_exit (4);
	}
	if (fk2 == 0)
	{
		close(pip[1]);
		ft_exit(ft_process(node->right, env));
	}
	close(pip[1]);
	close(pip[0]);
	waitpid(fk1, NULL, 0);
	waitpid(fk2, &status, 0);
	return (status);
}

int	ft_pipe(t_ast_node *node, char ***env)
{
	int		pip[2];
	int		fk1;

	if (pipe(pip) == -1)
	{
		perror("minishell: ");
		return (errno);
	}
	node->left->fd_out = pip[1];
	node->left->fd_in = node->fd_in;
	node->right->fd_in = pip[0];
	node->right->fd_out = node->fd_out;
	fk1 = fork();
	if (fk1 < 0)
	{
		perror("fork");
		ft_exit (errno);
	}
	if (fk1 == 0)
	{
		close(pip[0]);
		ft_process(node->left, env);
		ft_exit(0);
	}
	return (pipe_2(node, env, pip, fk1));
}
