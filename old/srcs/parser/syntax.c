#include "../../includes/headers/minishell.h"

t_bool	check_syntax(t_list *lst)
{
	t_list		*tmp;
	t_list		*tmp2;
	t_parser	*parser;
	t_parser	*tmp2_parser;

	tmp = lst;
	parser = tmp->content;
	if (parser->type != NODE_COMMAND && parser->type != NODE_REDIRECT_IN
		&& parser->type != NODE_REDIRECT_IN_HERE
		&& parser->type != NODE_REDIRECT_OUT
		&& parser->type != NODE_REDIRECT_OUT_APPENDS)
		return (FALSE);
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp2)
			tmp2_parser = tmp2->content;
		parser = tmp->content;
		if (!syntax_1(tmp2, tmp2_parser, parser) || !syntax_2(tmp2, tmp2_parser,
				parser))
			return (FALSE);
		tmp = tmp->next;
	}
	split_redirects(&lst);
	return (TRUE);
}

static t_bool	is_redirect(int type)
{
	if (type == NODE_REDIRECT_IN || type == NODE_REDIRECT_IN_HERE
		|| type == NODE_REDIRECT_OUT || type == NODE_REDIRECT_OUT_APPENDS)
		return (TRUE);
	return (FALSE);
}

t_bool	syntax_1(t_list *tmp2, t_parser *tmp2_parser, t_parser *parser)
{
	if (tmp2 == NULL && count_quotes(parser->str) % 2 != 0)
		return (FALSE);
	if (tmp2 && tmp2_parser->type == NODE_LOGICAL)
	{
		if (tmp2->next == NULL)
			return (FALSE);
		tmp2_parser = tmp2->next->content;
		if (parser->type == NODE_LOGICAL || parser->type == NODE_PIPE
			|| tmp2_parser->type == NODE_LOGICAL
			|| tmp2_parser->type == NODE_PIPE)
			return (FALSE);
	}
	if (tmp2 && tmp2_parser->type == NODE_PIPE)
	{
		if (tmp2->next == NULL)
			return (FALSE);
		tmp2_parser = tmp2->next->content;
		if (parser->type == NODE_LOGICAL || parser->type == NODE_PIPE
			|| is_redirect(parser->type) || tmp2_parser->type == NODE_LOGICAL
			|| tmp2_parser->type == NODE_PIPE)
			return (FALSE);
	}
	return (syntax_2(tmp2, tmp2_parser, parser));
}

t_bool	syntax_2(t_list *tmp2, t_parser *tmp2_parser, t_parser *parser)
{
	if (tmp2 && (tmp2_parser->type == NODE_REDIRECT_OUT
			|| tmp2_parser->type == NODE_REDIRECT_OUT_APPENDS
			|| tmp2_parser->type == NODE_REDIRECT_IN
			|| tmp2_parser->type == NODE_REDIRECT_IN_HERE))
	{
		if (tmp2->next == NULL)
			return (FALSE);
	}
	else if (!tmp2 && parser->type != NODE_COMMAND)
		return (FALSE);
	else if (tmp2 && tmp2_parser->type == NODE_UNKNOWN)
		return (FALSE);
	return (TRUE);
}

void	split_redirects(t_list **lst)
{
	t_list		*temp;
	t_list		*temp2;
	t_parser	*content;

	temp = *lst;
	while (temp != NULL)
	{
		content = temp->content;
		if (temp->next != NULL && is_redirect(content->type))
		{
			free(content->str);
			content->str = ft_strdup(((t_parser *)(temp->next->content))->str);
			temp2 = temp->next;
			temp->next = temp->next->next;
			ft_lstdelone(temp2, free_parse_lst);
		}
		temp = temp->next;
	}
}
