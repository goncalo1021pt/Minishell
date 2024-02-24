/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:29:18 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:29:18 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

static void sj_free(char *f)
{
	if (f)
		free(f);
}

char	*ft_strjoin_f1(char *s1, char const *s2)
{
	int		count;
	int		count2;
	char	*aux;

	aux = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (aux == NULL)
		return (sj_free (s1), NULL);
	count = 0;
	while (s1 && s1[count])
	{
		aux[count] = s1[count];
		count ++;
	}
	count2 = 0;
	while (s2 && s2[count2])
	{
		aux[count + count2] = s2[count2];
		count2 ++;
	}
	aux[count + count2] = '\0';
	return (sj_free(s1), aux);
}

char	*ft_strjoin_f2(char const *s1, char *s2)
{
	int		count;
	int		count2;
	char	*aux;

	aux = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (aux == NULL)
		return (sj_free (s2), NULL);
	count = 0;
	while (s1 && s1[count])
	{
		aux[count] = s1[count];
		count ++;
	}
	count2 = 0;
	while (s2 && s2[count2])
	{
		aux[count + count2] = s2[count2];
		count2 ++;
	}
	aux[count + count2] = '\0';
	return (sj_free(s2), aux);
}

char	*ft_strjoin_f12(char *s1, char *s2)
{
	int		count;
	int		count2;
	char	*aux;

	aux = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (aux == NULL)
		return (sj_free (s1), sj_free(s2), NULL);
	count = 0;
	while (s1 && s1[count])
	{
		aux[count] = s1[count];
		count ++;
	}
	count2 = 0;
	while (s2 && s2[count2])
	{
		aux[count + count2] = s2[count2];
		count2 ++;
	}
	aux[count + count2] = '\0';
	return (sj_free(s1), sj_free(s2), aux);
}
