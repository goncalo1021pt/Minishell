#include "../includes/headers/minishell.h"
/*
Counts the number of chars in (str)
stops counting at '\0' or (c)
Returns: number of counted chars
*/
static size_t	ft_strlen_c(char const *str, char c)
{
	size_t	count;

	count = 0;
	while ((str[count] != '\0') && (str[count] != c))
		count ++;
	return (count);
}

/*
Counts the number of words in (s) using c as the separator
Returns: number of words
*/
static size_t	ft_wordcount_c(char const *s, char c)
{
	size_t	count;
	size_t	i;
	int		check;

	count = 0;
	i = 0;
	check = 1;
	while (s[i])
	{
		if ((check == 1) && (s[i] != c))
		{
			count ++;
			check = 0;
		}
		else if (s[i] == c)
		{
			check = 1;
		}
		i ++;
	}
	return (count);
}

/*
Creates a new string from (str)
copies (str) stoping at '\0' or at c
Returns: the new string
*/
static char	*ft_strdup_c(char const *str, char c)
{
	size_t	size;
	char	*aux;

	size = ft_strlen_c(str, c);
	aux = (char *)malloc(sizeof(char) * (size + 1));
	if (!aux)
		return (NULL);
	aux[size] = '\0';
	while (size > 0)
	{
		aux[size - 1] = str[size - 1];
		size --;
	}
	return (aux);
}

static char	**ft_clean(char **sp, int count)
{
	while (count > 0)
	{
		if (sp[count])
			free(sp[count]);
		count --;
	}
	if (sp[count])
		free(sp[count]);
	free(sp);
	return (NULL);
}

/*
Separates (s) in strings separated by (c)
Returns: an array with the separated strings
*/
char	**ft_split(char const *s, char c)
{
	size_t	size;
	size_t	count_a;
	size_t	count_s;
	char	**aux_as;

	size = ft_wordcount_c(s, c);
	aux_as = (char **)malloc(sizeof (char *) * (size + 1));
	if (aux_as == NULL)
		return (NULL);
	aux_as[size] = NULL;
	count_a = 0;
	count_s = 0;
	while (count_a < size)
	{
		while (s[count_s] == c)
			count_s ++;
		aux_as[count_a] = ft_strdup_c(&s[count_s], c);
		if (!(aux_as[count_a]))
			return (ft_clean(aux_as, count_a));
		count_s = count_s + ft_strlen_c(&s[count_s], c);
		count_a ++;
	}
	return (aux_as);
}
/*
int main ()
{
    char	**aux;
	char	**aux2;
    int		i;

    aux2 = ft_split("abmvnmvgn ktufvjtfj 1123132    kgkygjyk   z  c  ",' ');
	aux = ft_astr_dup(aux2);
    i = 0;
    while (aux[i] != NULL)
    {
        printf("%s$\n", aux[i]);
        i ++;
    }
    return (0);
}
*/