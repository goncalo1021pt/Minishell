#include "../includes/headers/minishell.h"

static int	skip_quotes(const char *str, int ctd, char quote_type)
{
	ctd++;
	while (str[ctd] && str[ctd] != quote_type)
		ctd++;
	return (ctd + 1);
}

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
				ctd = skip_quotes(str, ctd, '\'');
			else if (str[ctd] == '\"')
				ctd = skip_quotes(str, ctd, '\"');
			else
				ctd++;
		}
	}
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
	{
		if (str[word_len] == '\'')
			word_len = skip_quotes(str, word_len, '\'');
		else if (str[word_len] == '\"')
			word_len = skip_quotes(str, word_len, '\"');
		else
			word_len++;
	}
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

char	**ft_split_quotes(char const *s, char c)
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
			if (!out[ctd])
				return (free_str(out, ctd - 1));
			while (*s && *s != c)
			{
				if (*s == '\'')
					s = s + skip_quotes(s, 0, '\'');
				else if (*s == '\"')
					s = s + skip_quotes(s, 0, '\"');
				else
					s++;
			}
			ctd++;
		}
	}
	out[ctd] = 0;
	return (out);
}
