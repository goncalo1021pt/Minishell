/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:29:14 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:29:14 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*stra;
	unsigned char	*strb;
	size_t			i;

	stra = (unsigned char *)s1;
	strb = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (1);
	while ((stra[i] == strb[i]) && (stra[i]))
		i++;
	return (stra[i] - strb[i]);
}
