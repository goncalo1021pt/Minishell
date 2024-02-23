/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:29:23 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:48 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

t_info	exit_info(char ***env, t_ast_node **tree)
{
	static t_info	info;

	if (env)
		info.env = env;
	if (tree)
		info.tree = tree;
	return (info);
}

int	err_info(int err)
{
	static int	error_code;

	if (err != EXIT_UNCHANGED)
		error_code = err;
	return (error_code);
}
