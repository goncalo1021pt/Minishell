/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:03 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:05 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

void	ft_exit(int status)
{
	t_info	info;

	info = exit_info(NULL, NULL);
	if (*(info.tree))
		ast_free(*(info.tree));
	if (*(info.env))
		clean_arr_str(*(info.env));
	exit(status);
}
