#include "../../includes/headers/minishell.h"

t_list *parse_to_list(char **args)
{
	t_list		*list;
	t_parser	*parser;
	int		ctd;

	ctd = 0;
	list = NULL;
	while (args[ctd])
	{
		parser = (t_parser *)malloc(sizeof(t_parser));
		if (!parser)
			return (NULL);
		set_type(parser, args, ctd);
		parser->str = ft_strdup(args[ctd]);
		ft_lstadd_back(&list, ft_lstnew(parser));
		ctd++;
	}
	return (list);
}

void set_type(t_parser *parser, char **args, int ctd)
{
	parser->type = NODE_COMMAND;
	if (!ft_strncmp(args[ctd], "||", 2) || !ft_strncmp(args[ctd], "&&", 2))
		parser->type = NODE_LOGICAL;
	else if (!ft_strncmp(args[ctd], "|", 1))
		parser->type = NODE_PIPE;
	else if (!ft_strncmp(args[ctd], ">>", 2))
		parser->type = NODE_REDIRECT_OUT_APPENDS;
	else if (!ft_strncmp(args[ctd], ">", 1))
		parser->type = NODE_REDIRECT_OUT;
	else if (!ft_strncmp(args[ctd], "<<", 2))
		parser->type = NODE_REDIRECT_IN_HERE;
	else if (!ft_strncmp(args[ctd], "<", 1))
		parser->type = NODE_REDIRECT_IN;
}
