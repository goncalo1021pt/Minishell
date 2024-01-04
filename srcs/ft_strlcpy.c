#include "../includes/headers/minishell.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while ((src[i] != '\0') && (i + 1 < size))
	{
		dest[i] = src[i];
		i ++;
	}
	if (size > 0)
		dest[i] = '\0';
	return (ft_strlen(src));
}