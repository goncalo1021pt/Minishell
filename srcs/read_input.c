#include "../includes/headers/minishell.h"

void *read_input(t_shell_list shell)
{
	char	*line;

	line = get_next_line(0);


	free(line);
}	
