#include "../includes/headers/minishell.h"

static int	skip_quotes(const char *str, int ctd, char quote_type)
{
	ctd++;
	while (str[ctd] && str[ctd] != quote_type)
		ctd++;
	return (ctd + 1);
}

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

char	**ft_split_quotes(char const *s)
{
	char	**out;
	int		ctd;

	ctd = 0;
	out = (char **)malloc((count_word(s) + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	while (*s)
	{
		while (*s && is_in_array(*s, SPACE_LIST))
			s++;
		if (*s)
		{
			out[ctd] = word_aloc(s);
			if (!out[ctd])
				return (free_str(out, ctd - 1));
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
	out[ctd] = 0;
	return (out);
}

int	copy_quotes(char *dst, char *src, char quote_type)
{
	int ctd;

	ctd = 1;
	dst[0] = src[0];
	while (src[ctd] && src[ctd] != quote_type)
	{
		dst[ctd] = src[ctd];
		ctd++;
	}
	dst[ctd] = src[ctd];
	return (ctd);
}

char *create_spaces(char *str)
{
	char *out;
	int new_len;
	int ctd;
	int ctd2;
	int	temp;

	new_len = ft_strlen(str);
	ctd = -1;
	while (str[++ctd])
	{
		if (str[ctd] == '\'' || str[ctd] == '\"')
			ctd = skip_quotes(str, ctd, str[ctd]);
		else if (is_in_array(str[ctd], ARGS_DIVISOR))
		{
			if (str[ctd + 1] == str[ctd])
				ctd++;
			new_len +=2;
		}
	}
	out = (char *)malloc(new_len + 1);
	if (!out)
		return (NULL);
	ctd = 0;
	ctd2 =  0;
	while (str[ctd])
	{
		if (str[ctd] == '\'' || str[ctd] == '\"')
		{
			temp = copy_quotes(out + ctd2 , str + ctd, str[ctd]);
			ctd += temp;
			ctd2 += temp;
		}
		else if (is_in_array(str[ctd], ARGS_DIVISOR))
		{
			out[ctd2++] = ' ';
			out[ctd2] = str[ctd];
			if (str[ctd + 1] == str[ctd])
				out[++ctd2] = str[++ctd];
			out[++ctd2] = ' ';
		}
		else
			out[ctd2] = str[ctd];
		ctd++;
		ctd2++;
	}
	out[ctd2] = 0;
	return (out);
}

char **ft_costume_split(char *str)
{
	char	*new_str;

	new_str = create_spaces(str);
	return (ft_split_quotes(new_str));
}

