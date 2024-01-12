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

create_apaces(){

}

/* char *aloc_special(char *str)
{
	char	*word;
	int		ctd;

	if (str[1] == str[0])
		ctd = 2;
	else
		ctd = 1;
	word = malloc(ctd + 1);
	if (!word)
		return (NULL);
	word[0] = str[0];
	if (ctd == 2)
		word[1] = str[1];
	word[ctd] = 0;
	return (word);
}

char *new_word(char *str)
{
	int		ctd;
	int		ctd2;
	char	*word;

	ctd = 0;
	ctd2 = 0;
	if (is_in_array(str[0], ARGS_DIVISOR))
	{
		return (aloc_special(str));
	}
	while (str[ctd] && !is_in_array(str[ctd], ARGS_DIVISOR))
		ctd++;
	word = (char *)malloc(ctd + 1);
	if (!word)
		return (NULL);
	while (ctd2 < ctd)
	{
		word[ctd2] = str[ctd2];
		ctd2++;
	}
	word[ctd2] = 0;
	return (word);
}

int count_spcial(char **args)
{
	int		ctd;
	int		ctd2;
	int		total;

	ctd = 0;
	total = 0;
	while (args[ctd]) // hello|ls // should be  args
	{
		ctd2 = 0;
		while (args[ctd][ctd2])
		{
			if (args[ctd][0] == '\'' || args[ctd][0] == '\"')
			{
				total++;
				break;
			}
			if (is_in_array(args[ctd][ctd2], ARGS_DIVISOR))
			{
				if (args[ctd][ctd2 + 1] == args[ctd][ctd2])
					ctd2++;
				total++;
			}
			ctd2++;
		}
		ctd++;
	}
	return (total);
}

char **split_special_args(char **args)
{
	int		ctd;
	int		ctd2;
	int		ctd3;
	int		total;
	char	**out;

	total = count_spcial(args);
	out = (char **)malloc((total + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	ctd = 0;
	ctd2 = 0;
	ctd3 = 0;
	while (args[ctd]) 
	{
		ctd2 = 0;
		while (args[ctd][ctd2])
		{
			if (args[ctd][0] == '\'' || args[ctd][0] == '\"')
			{
				out[ctd3] = ft_strdup(aloc_special(args[ctd]));
				ctd3++;
				break;
			}
			if (args[ctd][ctd2])
			{
				out[ctd3] = new_word(args[ctd], &ctd2);
				ctd3++;
			}
			ctd2++;
		}
		ctd++;
	}
	return (out);
} */
