/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:54 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/19 18:31:38 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

void	parser_to_tree(t_list **lst, t_ast_node **ast)
{
	t_list	*nod;
	t_list	*prev;

	if (!lst || !*lst)
		return ;
	else if (search_logical(*lst, &nod, &prev))
	{
		*ast = ast_new_node(nod->content);
		prev->next = NULL;
		parser_to_tree(lst, &((*ast)->left));
		parser_to_tree(&nod->next, &((*ast)->right));
		clean_lst(nod);
	}
	else if (search_pipe(*lst, &nod, &prev))
	{
		*ast = ast_new_node(nod->content);
		prev->next = NULL;
		parser_to_tree(lst, &((*ast)->left));
		parser_to_tree(&nod->next, &((*ast)->right));
		clean_lst(nod);
	}
	else
		cmd_parser(*lst, ast, 1);
	clean_lst(*lst);
	*lst = NULL;
}

static void	set_phantom_node(t_ast_node **ast)
{
	if (!(*ast))
	{
		*ast = ast_new_node(NULL);
		(*ast)->type = NODE_COMMAND;
	}
}

void	cmd_parser(t_list *lst, t_ast_node **ast, int first)
{
	t_parser	*content;

	if (lst && ast)
	{
		content = lst->content;
		set_phantom_node(ast);
		if (content->type == NODE_COMMAND)
		{
			if (first == 1)
			{
				(*ast)->value = ft_strdup(content->str);
				cmd_parser(lst->next, ast, 0);
			}
			else
			{
				add_full_right(*ast, ast_new_node(content));
				cmd_parser(lst->next, ast, first);
			}
		}
		else
		{
			add_full_left(*ast, ast_new_node(content));
			cmd_parser(lst->next, ast, first);
		}
	}
}

int	search_logical(t_list *lst, t_list **nod, t_list **prev)
{
	t_parser	*content;

	if (lst)
	{
		content = lst->content;
		if (content->type == NODE_LOGICAL)
		{
			*nod = lst;
			return (TRUE);
		}
		*prev = lst;
		return (search_logical(lst->next, nod, prev));
	}
	*nod = NULL;
	*prev = NULL;
	return (FALSE);
}

int	search_pipe(t_list *lst, t_list **nod, t_list **prev)
{
	t_parser	*content;

	if (lst)
	{
		content = lst->content;
		if (content->type == NODE_PIPE)
		{
			*nod = lst;
			return (TRUE);
		}
		*prev = lst;
		return (search_pipe(lst->next, nod, prev));
	}
	*nod = NULL;
	*prev = NULL;
	return (FALSE);
}
