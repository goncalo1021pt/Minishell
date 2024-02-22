/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:12 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:24 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	skip_quotes(const char *str, int ctd, char quote_type)
{
	ctd++;
	while (str[ctd] && str[ctd] != quote_type)
		ctd++;
	return (ctd);
}

int	copy_quotes(char *dst, char *src, char quote_type)
{
	int	ctd;

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

//a"""
int	count_quotes(char *str)
{
	int		ctd;
	int		count;
	char	temp;

	count = 0;
	ctd = 0;
	while (str[ctd])
	{
		if (str[ctd] == '\'' || str[ctd] == '\"')
		{
			temp = str[ctd];
			count++;
			ctd = skip_quotes(str, ctd, str[ctd]);
			if (str[ctd] == temp)
			{
				count++;
				ctd++;
			}
		}
		else
			ctd++;
	}
	return (count);
}

char	*remove_quotes(char *str)
{
	char	*out;
	int		ctd;
	int		ctd2;
	int		copied;

	out = ft_calloc(ft_strlen(str) - count_quotes(str) + 1, sizeof(char));
	if (!out)
		return (NULL);
	ctd = 0;
	ctd2 = 0;
	while (str[ctd])
	{
		if (str[ctd] == '\'' || str[ctd] == '\"')
		{
			copied = copy_in_quotes(out + ctd2, str + ctd, str[ctd]);
			ctd2 += copied;
			ctd += copied + 2;
		}
		else
			out[ctd2++] = str[ctd++];
	}
	free(str);
	return (out);
}

int	copy_in_quotes(char *dst, char *src, char quote_type)
{
	int	ctd;

	ctd = 1;
	while (src[ctd] && src[ctd] != quote_type)
	{
		dst[ctd - 1] = src[ctd];
		ctd++;
	}
	return (ctd - 1);
}
