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

void expand_wildcard(t_list *list)
{
	while (list)
	{
		if (((t_parser *)(list->content))->type == NODE_COMMAND && as_wildcard(((t_parser *)(list->content))->str))
			ft_wild(&list);
		printf("%pasd\n", list->next);
		list = list->next;
	}
}

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
