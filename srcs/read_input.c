#include "../includes/headers/minishell.h"

void	*read_input(t_shell_list *shell)
{
	char	*line;

	(void)shell;
	line = get_next_line(0);
	// ft_printf("line: %s", line);
	free(line);
	return (NULL);
}
