/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:29:20 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:48 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	my_alloc(size_t size, size_t len, void **dst)
{
	*dst = ft_calloc(len, size);
	if (*dst == NULL)
		return (1);
	else
		return (0);
}
