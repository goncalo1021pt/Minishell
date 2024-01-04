#include "../includes/headers/minishell.h"

size_t	ft_strlen(char const *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
		count ++;
	return (count);
}
