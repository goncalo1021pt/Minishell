#include "../../includes/headers/minishell.h"

static int	count_word(const char *str)
{
	int	ctd;
	int	total;

	ctd = 0;
	total = 0;
	while (str[ctd])
	{
		while (str[ctd] && is_in_array(str[ctd], SPACE_LIST))
			ctd++;
		if (str[ctd])
			total++;
		while (str[ctd] && !is_in_array(str[ctd], SPACE_LIST))
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

static char	*word_aloc(const char *str)
{
	char	*word;
	int		word_len;
	int		ctd;

	ctd = -1;
	word_len = 0;
	while (str[word_len] && !is_in_array(str[word_len], SPACE_LIST))
	{
		if (str[word_len] == '\'')
			word_len = skip_quotes(str, word_len, '\'');
		else if (str[word_len] == '\"')
			word_len = skip_quotes(str, word_len, '\"');
		else
			word_len++;
	}
	word = (char *)ft_calloc(word_len + 1, sizeof(char *));
	if (!word)
		return (NULL);
	while (++ctd < word_len)
		word[ctd] = str[ctd];
	return (word);
}

char	**ft_split_quotes(char const *s)
{
	char	**out;
	int		ctd;

	ctd = 0;
	out = (char **)ft_calloc((count_word(s) + 1), sizeof(char *));
	if (!out)
		return (NULL);
	return (skip_str((char *)s, out, ctd));
}

char **skip_str(char *s, char **out, int ctd)
{
	while (*s)
	{
		while (*s && is_in_array(*s, SPACE_LIST))
			s++;
		if (*s)
		{
			out[ctd] = word_aloc(s);
			if (!out[ctd])
				return (free_arr_str(out, ctd - 1));
		while (*s && !is_in_array(*s, SPACE_LIST))
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
	return (out);
}

char	**ft_custom_split(char *str)
{
	char	*new_str;
	char	**out;

	new_str = create_spaces(str);
	out = ft_split_quotes(new_str);
	free(new_str);
	return (out);
}
