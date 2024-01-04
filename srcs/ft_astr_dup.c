#include "../includes/headers/minishell.h"

char	**ft_astr_dup(char **astr)
{
	char	**aux;
	size_t	count;

	count = 0;
	while (astr[count])
		count++;
	if (my_alloc(sizeof(char *), count + 1, (void **)(&aux)))
		return (NULL);
	count = 0;
	while (astr[count])
	{
		aux[count] = ft_strdup(astr[count]);
		if (!aux[count])
		{
			clean_astr(aux);
			return (NULL);
		}
		count++;
	}
	return (aux);
}

char	**ft_astr_dup_add(char **astr, char *new)
{
	char	**aux;
	size_t	count;
	size_t	len;

	len = 0;
	while (astr && astr[len])
		len++;
	if (my_alloc(sizeof(char *), len + 2, (void **)(&aux)))
		return (NULL);
	count = 0;
	while (count < len)
	{
		aux[count] = ft_strdup(astr[count]);
		if (!aux[count])
		{
			clean_astr(aux);
			return (NULL);
		}
		count++;
	}
	aux[count] = new;
	return (aux);
}

char	**ft_astr_extend(char **astr, char *new)
{
	char	**aux;
	size_t	count;
	size_t	len;

	len = 0;
	while (astr && astr[len])
		len++;
	if (my_alloc(sizeof(char *), len + 2, (void **)(&aux)))
		return (NULL);
	count = 0;
	while (count < len)
	{
		aux[count] = astr[count];
		if (!aux[count])
		{
			free(aux);
			return (NULL);
		}
		count++;
	}
	aux[count] = new;
	return (aux);
}

/*
int main (int argc, char **argv, char **env)
{
    char	**aux;
    int		i;

	aux = ft_astr_dup(env);
    i = 0;
    while (aux[i] != NULL)
    {
        printf("%s\n", aux[i]);
        i ++;
    }
    return (0);
}
*/