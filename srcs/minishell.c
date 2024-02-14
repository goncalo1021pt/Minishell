#include "../includes/headers/minishell.h"

/* 
The grammar below is written in Backus-Naur Form (BNF) - https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form

<command line> : <and or> ';' <command line>	; in the code, this is of type AST_SEQ, as it's a sequence of commands
               | <and or> ';'
               | <and or>
               ;

<and or>       : <job> '&&' <and or>
               | <job> '||' <and or>
               | <job>
               ;

<job>          : <command> '|' <job>
               | <command>
               ;

<command>      : <token list>
               ;

<token list>   : [name]  <token list>
               | [token] <token list>
               | [redir] <token list>
               | (null)
               ;

<redir>        : <redir in>
               | <redir out>
               ;

<redir in>     : '<<' [file]
               | '<'  [file]
               ;

<redir out>    : '>>' [file]
               | '>'  [file]
               ;

The symbology above can be easily explained if we follow a bottom-up approach, starting with the individual definitions.
- Heredoc is the use of "<<" followed by a termiator
- A word is any string correctly quoted
- A redirection is considered the use of "<", ">", or ">>" followed by a filename

Having the basic definitions understood we can start getting into the recursive definitionsw of the other parts.
- A command can be comprised of a single word ("ls"), redirection ("> test.txt"), or a heredoc ("<< EOF"). Additionally,
	a command can also be defined as a series words, redirections, or a combination of both ("ls -l > out.txt").
- A pipeline can be defined as a single command (as defined above), or as a series of commands concatenated by a "|"
 */

int	minishell(char ***env)
{
	char			*line;
	char 			**args;
	char			*promt;
	t_ast_node		*ast;
	t_list			*list;

	// choose_signal(ROOT);
	exit_info(env, &ast);
	while (1)
	{
		choose_signal(ROOT);
		ast = NULL;
		list = NULL;
		promt = get_prompt();
		line = readline(promt);
		free(promt);
		if (!line)
			ft_exit(0);
		if (!*line || is_in_array(*line, SPACE_LIST))
		{
			free(line);
			continue ;
		}
		if (line[0] != '\0')
			add_history(line);
		args = ft_custom_split(line, *env);
		free(line);
		list = parse_to_list(args);
		clean_arr_str(args);
		if (!check_syntax(list))
		{
			ft_putendl_fd("syntax error", 2);
			err_info(2);
			free_all(list);
			continue ;
		}
		expand_lst(list, *env);
		// ft_lstiter(list, print_content);
		parser(&list, &ast);
		// print_tree(ast);
		err_info(call_process(ast, env));
		ast_free(ast);
	}
}

void free_all(t_list *list)
{
	ft_lstclear(&list, free_parse_lst);
}


void print_content(void *p)
{
	t_parser	*parser;

	parser = p;
	ft_printf("String: %s, Type: %d\n", parser->str, parser->type);
}

void free_parse_lst(void *content)
{
	t_parser	*parser;

	parser = content;
	free(parser->str);
	free(parser);
}

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
		parser->str = ft_strdup(args[ctd]);
		ft_lstadd_back(&list, ft_lstnew(parser));
		ctd++;
	}
	return (list);
}

t_bool check_syntax(t_list *lst)
{
	t_list	*tmp;
	t_list	*tmp2;
	t_parser	*parser;
	t_parser	*tmp2_parser;

	tmp = lst;
	parser = tmp->content;
	if (parser->type != NODE_COMMAND && parser->type != NODE_REDIRECT_IN && parser->type != NODE_REDIRECT_IN_HERE && parser->type != NODE_REDIRECT_OUT && parser->type != NODE_REDIRECT_OUT_APPENDS)
		return (FALSE);
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp2)
			tmp2_parser = tmp2->content;
		parser = tmp->content;
		if (tmp->next == NULL && count_quotes(parser->str) % 2 != 0)
			return (FALSE);
		if (tmp2 && tmp2_parser->type == NODE_LOGICAL)
		{
			if (tmp2->next == NULL)
				return (FALSE);
			tmp2_parser = tmp2->next->content;
			if (parser->type == NODE_LOGICAL || parser->type == NODE_PIPE || tmp2_parser->type == NODE_LOGICAL || tmp2_parser->type == NODE_PIPE)
				return (FALSE);
		}
		else if (tmp2 && tmp2_parser->type == NODE_PIPE)
		{
			if (tmp2->next == NULL)
				return (FALSE);
			tmp2_parser = tmp2->next->content;
			if (parser->type == NODE_LOGICAL || parser->type == NODE_PIPE || tmp2_parser->type == NODE_LOGICAL || tmp2_parser->type == NODE_PIPE)
				return (FALSE);
		}
		else if (tmp2 && (tmp2_parser->type == NODE_REDIRECT_OUT || tmp2_parser->type == NODE_REDIRECT_OUT_APPENDS || tmp2_parser->type == NODE_REDIRECT_IN || tmp2_parser->type == NODE_REDIRECT_IN_HERE))
		{
			if (tmp2->next == NULL)
				return (FALSE);
			tmp2_parser = tmp2->next->content;
			if (tmp2_parser->type != NODE_COMMAND)
				return (FALSE);
		}
		tmp = tmp->next;
	}
	split_redirects(&lst);
	return (TRUE);
}

void split_redirects(t_list **lst)
{
	t_list 		*temp;
	t_list		*temp2;
	t_parser	*content;

	temp = *lst;
	while (temp != NULL)
	{
		content = temp->content;
		if (temp->next != NULL && (content->type == NODE_REDIRECT_OUT || content->type == NODE_REDIRECT_OUT_APPENDS || content->type == NODE_REDIRECT_IN || content->type == NODE_REDIRECT_IN_HERE))
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

int ft_arrlen(char **arr)
{
	int		ctd;

	ctd = 0;
	while (arr && arr[ctd])
		ctd++;
	return (ctd);
}

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

void parser(t_list **lst, t_ast_node **ast)
{
	t_list	*nod;
	t_list *prev;

	if(!lst || !*lst)
		return ;
	else if(search_logical(*lst, &nod, &prev))
	{
		*ast = ast_new_node(nod->content);
		prev->next = NULL;
		parser(lst, &((*ast)->left));
		parser(&nod->next, &((*ast)->right));
	}
	else if(search_pipe(*lst, &nod, &prev))
	{
		*ast = ast_new_node(nod->content);
		prev->next = NULL;
		parser(lst, &((*ast)->left));
		parser(&nod->next, &((*ast)->right));
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
		if(!(*ast))
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
			return(TRUE);
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
			return(TRUE);
		}
		*prev = lst;
		return (search_pipe(lst->next, nod, prev));
	}
	*nod = NULL;
	*prev = NULL;
	return (FALSE);
}

char	*trim_path(char *path)
{
	char	*new_path;
	int		ctd;

	ctd = ft_strlen(path);
	while (path[ctd] != '/')
		ctd--;
	ctd++;
	new_path = ft_strdup(path + ctd);
	free(path);
	return (new_path);
}

char	*get_prompt(void)
{
	char	*pwd;
	char	*prompt;

	pwd = get_current_pwd();
	pwd = trim_path(pwd);
	prompt = ft_strjoin_f1(pwd, "$ ");
	prompt = ft_strjoin_f2("Minishell> ", prompt);
	return (prompt);
}
