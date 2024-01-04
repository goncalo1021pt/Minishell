#include "../includes/headers/minishell.h"

/*
Creates a new string
the new string is (s1) with (s2) added at the end
Return: the new string
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		count;
	int		count2;
	char	*aux;

	aux = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (aux == NULL)
		return (NULL);
	count = 0;
	while (s1[count])
	{
		aux[count] = s1[count];
		count ++;
	}
	count2 = 0;
	while (s2[count2])
	{
		aux[count + count2] = s2[count2];
		count2 ++;
	}
	aux[count + count2] = '\0';
	return (aux);
}

char	*ft_strjoin_f1(char *s1, char const *s2)
{
	int		count;
	int		count2;
	char	*aux;

	aux = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (aux == NULL)
		return (free (s1), NULL);
	count = 0;
	while (s1[count])
	{
		aux[count] = s1[count];
		count ++;
	}
	count2 = 0;
	while (s2[count2])
	{
		aux[count + count2] = s2[count2];
		count2 ++;
	}
	aux[count + count2] = '\0';
	return (free(s1), aux);
}

char	*ft_strjoin_f2(char const *s1, char *s2)
{
	int		count;
	int		count2;
	char	*aux;

	aux = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (aux == NULL)
		return (free (s2), NULL);
	count = 0;
	while (s1[count])
	{
		aux[count] = s1[count];
		count ++;
	}
	count2 = 0;
	while (s2[count2])
	{
		aux[count + count2] = s2[count2];
		count2 ++;
	}
	aux[count + count2] = '\0';
	return (free(s2), aux);
}

char	*ft_strjoin_f12(char *s1, char *s2)
{
	int		count;
	int		count2;
	char	*aux;

	aux = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (aux == NULL)
		return (free (s1), free(s2), NULL);
	count = 0;
	while (s1[count])
	{
		aux[count] = s1[count];
		count ++;
	}
	count2 = 0;
	while (s2[count2])
	{
		aux[count + count2] = s2[count2];
		count2 ++;
	}
	aux[count + count2] = '\0';
	return (free(s1), free(s2), aux);
}
