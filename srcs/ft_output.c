#include "../includes/headers/minishell.h"

void	ft_output(char *str, int fd)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		write(fd, &(str[i]), 1);
		i++;
	}
}

void	ft_output_nl(char *str, int fd)
{
	ft_output(str, fd);
	write(fd, "\n", 1);
}
