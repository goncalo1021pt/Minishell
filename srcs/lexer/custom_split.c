/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:05 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:20 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**skip_str(char *s, char **out, int ctd)
{
	int	ctd2;

	ctd2 = 0;
	while (s[ctd2])
	{
		while (s[ctd2] && is_in_array(s[ctd2], SPACE_LIST))
			ctd2++;
		if (s[ctd2])
		{
			out[ctd] = word_aloc(s + ctd2);
			if (!out[ctd])
				return (free_arr_str(out, ctd - 1));
			while (s[ctd2] && !is_in_array(s[ctd2], SPACE_LIST))
			{
				if (s[ctd2] == '\'')
					ctd2 = ctd2 + skip_quotes(s + ctd2, 0, '\'');
				if (s[ctd2] == '\"')
					ctd2 = ctd2 + skip_quotes(s + ctd2, 0, '\"');
				ctd2++;
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
	int		total;

	total = count_quotes(str);
	if (total % 2 != 0)
		return (ft_putendl_fd("syntax error", 2), NULL);
	new_str = create_spaces(str);
	out = ft_split_quotes(new_str);
	free(new_str);
	return (out);
}
