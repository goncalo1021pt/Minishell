/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:39:18 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/28 14:36:59 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

void	free_hd(char *fname, int mode)
{
	if (!mode && fname)
		free(fname);
}

int	ft_get_here(t_ast_node *node)
{
	t_ast_node	*aux;
	int			ret;

	ret = 0;
	aux = node->left;
	while (aux)
	{
		if (aux->type == NODE_REDIRECT_IN_HERE && aux->value)
			ret = ft_read_del(aux, aux->value);
		if (ret)
			return (ret);
		aux = aux->left;
	}
	return (ret);
}

int	ft_read_amb(char *value)
{
	ft_output("minishell: ", STDOUT_FILENO);
	ft_output(value, STDOUT_FILENO);
	ft_output_nl(": ambiguous redirect", STDOUT_FILENO);
	return (1);
}
