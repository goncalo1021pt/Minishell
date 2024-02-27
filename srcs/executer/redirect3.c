/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:39:18 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/27 17:52:51 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

int	ft_read_amb(char *value)
{
	ft_output("minishell: ", STDOUT_FILENO);
	ft_output(value, STDOUT_FILENO);
	ft_output_nl(": ambiguous redirect", STDOUT_FILENO);
	return (1);
}
