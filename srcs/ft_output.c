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

void	ft_output_export(char *str, int fd)
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	while(str[i])
	{
		write(fd, &(str[i]), 1);
		if (check == 0 && str[i] == '=')
			write(fd, "\"", 1);
		i++;
	}
	write(fd, "\"\n", 2);
}