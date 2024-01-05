#include "../includes/headers/minishell.h"

char	*ft_strdup(const char *str)
{
	char	*aux;
	size_t	size;

	if (!str)
		return (NULL);
	size = ft_strlen(str);
	aux = (char *)malloc(sizeof(char) * (size + 1));
	if (aux == NULL)
		return (NULL);
	aux[size] = '\0';
	while (size > 0)
	{
		size --;
		aux[size] = str[size];
	}
	return (aux);
}
