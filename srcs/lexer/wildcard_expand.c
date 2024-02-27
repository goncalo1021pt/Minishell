#include "../../includes/headers/minishell.h"

static t_bool	as_wildcard(char *str)
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

static t_bool	prev_exists(t_list **new, t_list **current, t_list **prev)
{
	t_list		*temp;

	temp = ft_lstlast(*new);
	temp->next = (*current)->next;
	(*prev)->next = *new;
	free_parse_lst((*current)->content);
	free(*current);
	*current = temp->next;
	*prev = temp;
	return (TRUE);
}

void	prev_doesnt_exist(t_list **new, t_list **current, t_list **list)
{
	t_list		*temp;

	temp = ft_lstlast(*new);
	temp->next = (*current)->next;
	*list = *new;
	free_parse_lst((*current)->content);
	free(*current);
	*current = temp;
}

void	expand_wildcard(t_list **list)
{
	t_list		*current;
	t_parser	*content;
	t_list		*prev;
	t_list		*new;

	current = *list;
	prev = NULL;
	while (current)
	{
		content = current->content;
		if (as_wildcard(content->str))
		{
			new = ft_wild(content->str, content->type);
			ft_lstiter(new, print_content);
			if (new)
			{
				if (prev && prev_exists(&new, &current, &prev))
					continue ;
				else
					prev_doesnt_exist(&new, &current, list);
			}
		}
		prev = current;
		current = current->next;
	}
}

void	remove_quotes_lst(t_list *lst)
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
