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
	}
	else if (search_pipe(*lst, &nod, &prev))
	{
		*ast = ast_new_node(nod->content);
		prev->next = NULL;
		parser_to_tree(lst, &((*ast)->left));
		parser_to_tree(&nod->next, &((*ast)->right));
	}
	else
	{
		cmd_parser(*lst, ast, 1);
	}
	clean_lst(*lst);
	*lst = NULL;
}

void	cmd_parser(t_list *lst, t_ast_node **ast, int first)
{
	t_parser	*content;

	if (lst && ast)
	{
		content = lst->content;
		if (!(*ast))
		{
			*ast = ast_new_node(NULL);
			(*ast)->type = NODE_COMMAND;
		}
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
