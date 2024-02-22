/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:09 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:06 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	ft_pwd(int fd_out)
{
	char	*pwd;

	pwd = get_current_pwd();
	if (!pwd)
		return (0);
	ft_output_nl(pwd, fd_out);
	free(pwd);
	return (0);
}
