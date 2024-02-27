#include "../../includes/headers/minishell.h"

static t_bool as_wildcard(char *str)
{
	int	ctd;

	ctd = 0;
	while (str[ctd])
	{
		if (str[ctd] == '\'' || str[ctd] == '\"')
			ctd = skip_quotes(str, ctd, str[ctd]);
		if (str[ctd] == '*')
			return (TRUE);
		ctd++;
	}
	return (FALSE);
}

void expand_wildcard(t_list **list)
{
	t_list *current;
	t_parser *content;
	t_list *prev;
	t_list *new;
	t_list *temp;

	current = *list;
	prev = NULL;
	while (current)
	{
		content = current->content;
		if ((content->type == NODE_COMMAND) && as_wildcard(content->str))
		{
			new = ft_wild(content->str, content->type);
			if (new)
			{
				if (prev)
				{
					temp = ft_lstlast(new);
					temp->next = current->next;
					prev->next = new;
					free_parse_lst(current->content);
					free(current);
					current = temp->next;
					prev = temp;
					continue;
				}
				else
				{
					ft_lstlast(new)->next = current->next;
					temp = *list;
					*list = new;
					free_parse_lst(temp->content);
				}
			}
		}
		prev = current;
		current = current->next;
	}
}

// void expand_wildcard(t_list **list)
// {
// 	t_list *new;
// 	t_list *temp;
// 	t_list *prev;
// 	t_bool changed;

// 	prev = NULL;
// 	changed = FALSE;
// 	while (list)
// 	{

// 		if (((t_parser *)(list->content))->type == NODE_COMMAND && as_wildcard(((t_parser *)(list->content))->str))
// 		{
// 			temp = list->next;
// 			new = ft_wild(((t_parser *)(list->content))->str);
// 			if (new)
// 			{
// 				changed = TRUE;
// 				if (prev)
// 					prev->next = new;
// 				else
// 					list = new;
// 				ft_lstlast(new)->next = temp;
// 			}
// 		}
// 		prev = list;
// 		list = list->next;
// 		if (changed)
// 		{
// 			changed = FALSE;
// 			free_parse_lst(prev->content);
// 			free(prev);
// 			prev = temp;
// 		}
// 	}
// }

void remove_quotes_lst(t_list *lst)
{
	t_list		*start;
	t_parser	*content;

	start = lst;
	while (lst)
	{
		content = lst->content;
		if (content->type != NODE_REDIRECT_IN_HERE)
		{
			content->str = remove_quotes(content->str);
			if (!content->str)
			{
				free_all(start);
				err_info(ENOMEM);
				return ;
			}
		}
		lst = lst->next;
	}
}
