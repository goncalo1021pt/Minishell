#include "../includes/headers/minishell.h"

void	ft_output(char *str, int fd)
{
	printf("%s", str);
}

void	ft_output_nl(char *str, int fd)
{
	printf("%s\n", str);
}