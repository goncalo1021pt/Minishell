/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:14 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:24 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

static int	aloc_len(char *str)
{
	int	new_len;
	int	ctd;

	new_len = ft_strlen(str);
	ctd = -1;
	while (str[++ctd])
	{
		if (str[ctd] == '\'' || str[ctd] == '\"')
			ctd = skip_quotes(str, ctd, str[ctd]) - 1;
		else if (is_in_array(str[ctd], ARGS_DIVISOR))
		{
			if (str[ctd + 1] == str[ctd])
				ctd++;
			new_len += 2;
		}
	}
	return (new_len);
}

void	create_token(char *str, int ctd, int ctd2, char *out)
{
	int	temp;

	while (str[ctd])
	{
		if (str[ctd] == '\'' || str[ctd] == '\"')
		{
			temp = copy_quotes(out + ctd2, str + ctd, str[ctd]);
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
}

char	*create_spaces(char *str)
{
	char	*out;
	int		new_len;

	new_len = aloc_len(str);
	out = (char *)ft_calloc(new_len + 1, sizeof(char *));
	if (!out)
		return (NULL);
	create_token(str, 0, 0, out);
	return (out);
}

char	*add_to_middle(char *src, char *to_add, int ctd, int len)
{
	char	*out;
	int		len2;
	int		ctd2;

	len2 = ft_strlen(src) + ft_strlen(to_add) - len;
	out = ft_calloc(len2 + 1, sizeof(char));
	if (!out)
		return (NULL);
	ft_strncpy(out, src, ctd);
	ctd2 = 0;
	while (to_add && to_add[ctd2])
	{
		out[ctd + ctd2] = to_add[ctd2];
		ctd2++;
	}
	ctd++;
	while (src[ctd + len])
	{
		out[ctd + ctd2 - 1] = src[ctd + len];
		ctd++;
	}
	return (out);
}
