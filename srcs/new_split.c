#include <stdio.h>
#include <stdlib.h>

int check_special_char(char *str, char c, int ctd);

static int	count_word(char *str, char c)
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
		ctd = check_special_char(str, c, ctd);
	}
	return (total);
}

int check_special_char(char *str, char c, int ctd)
{
	while (str[ctd] && str[ctd] != c)
	{
		ctd++;
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
	return (ctd);
}

static char	*word_aloc(char *str, char c)
{
	char	*word;
	int		word_len;
	int		ctd;

	ctd = -1;
	word_len = 0;
	// while (str[word_len] && str[word_len] != c)
	// 	word_len++;
	check_special_char(str, c, word_len);
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

char **ft_special_split(char *str, char c)
{
	char	**out;
	int		ctd;
	int		ctd2;

	ctd = 0;
	ctd2 = 0;
	out = (char **)malloc(sizeof(char *) * (count_word(str, c) + 1));
	if (!out)
		return (NULL);
	while (str[ctd])
	{
		while (str[ctd] && str[ctd] == c)
			ctd++;
		if (str[ctd])
		{
			out[ctd2] = word_aloc(str + ctd, c);
			if (!out[ctd2])
				return (free_str(out, ctd2));
			ctd2++;
		}
		ctd = check_special_char(str, c, ctd);
	}
	out[ctd2] = NULL;
	return (out);
}

int main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	char *str = "teste 'dentro de aspas simples' \"dentro de aspas duplas\"";
	printf("%d\n", count_word(str, ' '));
	return (0);
}
