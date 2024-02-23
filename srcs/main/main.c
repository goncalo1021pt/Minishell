/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:18 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/22 13:03:11 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	**my_env;

	(void)argv;
	if (argc != 1)
		return (1);
	my_env = ft_astr_dup(env);
	shell_level(&my_env);
	minishell(&my_env);
	return (0);
}
