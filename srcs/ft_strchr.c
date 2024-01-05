#include "../includes/headers/minishell.h"

char	*ft_strchr(const char *str, int c)
{
	char	*res;
	size_t	count;

	if (!str)
		return (NULL);
	res = (char *)str;
	count = 0;
	while (res[count])
	{
		if (res[count] == (char)c)
			return ((char *)&res[count]);
		count ++;
	}
	if ((char)c == '\0')
		return ((char *)&res[count]);
	else
		return (NULL);
}
