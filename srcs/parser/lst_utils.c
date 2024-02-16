#include "../../includes/headers/minishell.h"

void	free_all(t_list *list)
{
	ft_lstclear(&list, free_parse_lst);
}

void	print_content(void *p)
{
	t_parser	*parser;

	parser = p;
	ft_printf("String: %s, Type: %d\n", parser->str, parser->type);
}

void	free_parse_lst(void *content)
{
	t_parser	*parser;

	parser = content;
	free(parser->str);
	free(parser);
}

void	clean_lst(t_list *lst)
{
	if (lst)
	{
		clean_lst(lst->next);
		if (lst->content)
		{
			if (((t_parser *)(lst->content))->str)
				free(((t_parser *)(lst->content))->str);
			free((t_parser *)(lst->content));
		}
		free(lst);
	}
}
