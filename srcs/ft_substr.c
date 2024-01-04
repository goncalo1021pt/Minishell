#include "../includes/headers/minishell.h"

/*
Creates a substring from the given string (s)
the new string will beggin at (start) and size (len)
Return: the string created
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*aux;
	size_t			size;
	size_t			t_len;
	unsigned int	count;

	count = 0;
	size = ft_strlen(s);
	if (size < start)
		t_len = 0;
	else if (size < start + len)
		t_len = size - start;
	else
		t_len = len;
	aux = (char *)malloc(sizeof(char) * (t_len + 1));
	if (aux == NULL)
		return (NULL);
	count = 0;
	while ((count < t_len) && (s[count]))
	{
		aux[count] = s[count + start];
		count ++;
	}
	aux[count] = '\0';
	return (aux);
}
/*
int main()
{
    char *s1 = "1234567890";
    printf("\n%s\n",ft_substr(s1, 3, 50));
    return (0);
}
*/
