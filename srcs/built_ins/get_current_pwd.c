/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_current_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:14 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:08 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

char	*get_current_pwd(void)
{
	char	buffer[MAX_PATH_SIZE];
	char	*ret;
	int		i;

	i = 0;
	while (i < MAX_PATH_SIZE)
	{
		buffer[i] = 0;
		i ++;
	}
	getcwd(buffer, MAX_PATH_SIZE);
	ret = ft_strdup(buffer);
	return (ret);
}
