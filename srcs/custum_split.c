#include <stdlib.h>
#include <stdio.h>

static int	count_word(const char *str, char c)
{
	int	ctd;
	int	total;

	ctd = 0;
	total = 0;
	while (str[ctd])
	{
		while (str[ctd] && str[ctd] == c)
			ctd++;
		if (str[ctd])
			total++;
		while (str[ctd] && str[ctd] != c)
		{
			if (str[ctd] == '\'')
			{
				ctd++;
				while (str[ctd] && (str[ctd] != '\''))
					ctd++;
			}
			else if (str[ctd] == '\"' )
			{
				ctd++;
				while (str[ctd] && str[ctd] != '\"')
					ctd++;
			}
			ctd++;
		}
	}
	printf("%d\n", total);
	return (total);
}

static char	*word_aloc(const char *str, char c)
{
	char	*word;
	int		word_len;
	int		ctd;

	ctd = -1;
	word_len = 0;
	while (str[word_len] && str[word_len] != c)
		word_len++;
	word = (char *)malloc(word_len + 1);
	if (!word)
		return (NULL);
	while (++ctd < word_len)
		word[ctd] = str[ctd];
	word[ctd] = '\0';
	return (word);
}

static	void	*free_str(char **out, int ctd)
{
	while (ctd >= 0)
		free(out[ctd--]);
	free(out);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**out;
	int		ctd;

	ctd = 0;
	out = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			out[ctd] = word_aloc(s, c);
			if (!out[ctd++])
				return (free_str(out, ctd));
		}
		while (*s && *s != c)
		{
			if (*s == '\'')
			{
				s++;
				while (*s && *s != '\'')
					s++;
			}
			else if (*s == '\"' )
			{
				s++;
				while (*s && *s != '\"')
					s++;
			}
			s++;
		}
			s++;
	}
	out[ctd] = 0;
	return (out);
}

int main()
{
	char **out;
	char *str = "hello world 'teste de varias palavras'";
	out = ft_split(str, ' ');
	printf("%s\n", out[0]);
	printf("%s\n", out[1]);
	return (0);
}