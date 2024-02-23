/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:44 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:35 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

void	print_tree(t_ast_node *node)
{
	if (node)
	{
		ft_printf("%i :: %s\n", node->type, node->value);
		ft_printf("\n%s LEFT\n", node->value);
		print_tree(node->left);
		ft_printf("\n%s RIGHT\n", node->value);
		print_tree(node->right);
	}
}
