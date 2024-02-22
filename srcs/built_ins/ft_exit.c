/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:03 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/22 11:33:09 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

static void	fuck_fds(void)
{
	size_t	fd;

	fd = 3;
	while (fd < FOPEN_MAX)
	{
		close(fd);
		fd++;
	}
}

void	ft_exit(int status)
{
	t_info	info;

	info = exit_info(NULL, NULL);
	if (*(info.tree))
		ast_free(*(info.tree));
	if (*(info.env))
		clean_arr_str(*(info.env));
	fuck_fds();
	exit(status);
}
