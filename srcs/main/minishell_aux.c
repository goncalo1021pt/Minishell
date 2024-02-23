/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:23 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:32 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

t_bool	has_argument(char *str)
{
	int	ctd;

	ctd = -1;
	while (str[++ctd])
		if (!is_in_array(str[ctd], SPACE_LIST))
			return (FALSE);
	return (TRUE);
}
