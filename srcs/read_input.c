#include "../includes/headers/minishell.h"

void	*read_input(t_shell_list *shell, char *promt)
{
	char	*line;

	(void)shell;
	line = readline(promt);
	if (!line)
		exit(0);
	free(promt);
	free(line);
	return (NULL);
}
