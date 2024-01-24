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

int	minishell(char **env)
{
	char			*line;
	char 			**args;
	char			*promt;
	t_ast_node		ast;

	(void)env;
	(void)ast;
	root_signals();
	while (1)
	{
		promt = get_prompt();
		line = readline(promt);
		if (!line)
			ft_exit(0);
		if (line[0] != '\0')
			add_history(line);
		args = ft_costume_split(line);
		print_arr_str(args);
		free(promt);
		free(line);
		clean_arr_str(args);
	}
}

t_list *parse_to_list(char **args)
{
	t_list	*list;
	t_parser	*parser;
	int		ctd;

	ctd = 0;
	list = NULL;
	while (args[ctd])
	{
		parser = malloc(sizeof(t_parser));
		if (!parser)
			return (NULL);
		if (ft_strncmp(args[ctd], "||", 2) || ft_strncmp(args[ctd], "&&", 2))
		{
			parser->type = NODE_LOGICAL;
			parser->str = ft_strdup(args[ctd]);
		}
		else if (ft_strncmp(args[ctd], "|", 1))
		{
			parser->type = NODE_PIPE;
			parser->str = ft_strdup(args[ctd]);
		}
		else if (ft_strncmp(args[ctd], ">", 1))
		{
			parser->type = NODE_REDIRECT_OUT;
			parser->str = ft_strdup(args[ctd]);
		}
		else if (ft_strncmp(args[ctd], ">>", 2))
		{
			parser->type = NODE_REDIRECT_OUT_APPENDS;
			parser->str = ft_strdup(args[ctd]);
		}
		else if (ft_strncmp(args[ctd], "<", 1))
		{
			parser->type = NODE_REDIRECT_IN;
			parser->str = ft_strdup(args[ctd]);
		}
		else if (ft_strncmp(args[ctd], "<<", 2))
		{
			parser->type = NODE_REDIRECT_IN_HERE;
			parser->str = ft_strdup(args[ctd]);
		}
		else
		{
			parser->type = NODE_ARGUMENT;
			parser->str = ft_strdup(args[ctd]);
		}
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
	if (parser->type != NODE_ARGUMENT)
		return (FALSE);
	while (tmp)
	{
		tmp2 = tmp->next;
		tmp2_parser = tmp2->content;
		parser = tmp->content;
		if (tmp2_parser->type == NODE_LOGICAL)
		{
			if (tmp2->next == NULL)
				return (FALSE);
			tmp2_parser = tmp2->next->content;
			if (parser->type == NODE_LOGICAL || parser->type == NODE_PIPE || tmp2_parser->type == NODE_LOGICAL || tmp2_parser->type == NODE_PIPE)
				return (FALSE);
		}
		else if (tmp2_parser->type == NODE_PIPE)
		{
			if (tmp2->next == NULL)
				return (FALSE);
			tmp2_parser = tmp2->next->content;
			if (parser->type == NODE_LOGICAL || parser->type == NODE_PIPE || tmp2_parser->type == NODE_LOGICAL || tmp2_parser->type == NODE_PIPE)
				return (FALSE);
		}
		else if (tmp2_parser->type == NODE_REDIRECT_OUT || tmp2_parser->type == NODE_REDIRECT_OUT_APPENDS || tmp2_parser->type == NODE_REDIRECT_IN || tmp2_parser->type == NODE_REDIRECT_IN_HERE)
		{
			if (tmp2->next == NULL)
				return (FALSE);
			tmp2_parser = tmp2->next->content;
			if (tmp2_parser->type != NODE_ARGUMENT)
				return (FALSE);
		}
		tmp = tmp->next;
	}
	return (TRUE);
}

char **split_args1(char **args, int ctd)
{
	char	**new_args;
	int		ctd2;

	ctd2 = 0;
	new_args = malloc(sizeof(char *) * (ctd + 1));
	if (!new_args)
		return (NULL);
	while (ctd2 < ctd)
	{
		new_args[ctd2] = ft_strdup(args[ctd2]);
		ctd2++;
	}
	new_args[ctd2] = NULL;
	return (new_args);
}

int ft_arrlen(char **arr)
{
	int		ctd;

	ctd = 0;
	while (arr && arr[ctd])
		ctd++;
	return (ctd);
}

char **split_args2(char **args, int ctd)
{
	char	**new_args;
	int		ctd2;

	ctd2 = 0;
	new_args = malloc(sizeof(char *) * (ft_arrlen(args) - ctd + 1));
	while (args[ctd])
	{
		new_args[ctd2] = ft_strdup(args[ctd]);
		ctd2++;
		ctd++;
	}
	new_args[ctd2] = NULL;
	return (new_args);
}

void parser(char **args, t_ast_node *ast, char add_direction)
{
	int			ctd;
	int			flag;

	ctd = 0;
	flag = 0;
	while (args[ctd] && flag < 3)
	{
		if (flag == 0 && args[ctd] && (ft_strncmp(args[ctd], "||", 2) || ft_strncmp(args[ctd], "&&", 2)))
		{
			ast_add_node(ast, ast_new_node(NODE_LOGICAL, args[ctd]), add_direction);
			parser(split_args1(args, ctd), ast, 'l');
			parser(split_args2(args, ctd), ast, 'r' );
			clean_arr_str(args);
		}
		if (flag == 1 && args[ctd] && (ft_strncmp(args[ctd], "|", 1)))
		{
			ast_add_node(ast, ast_new_node(NODE_PIPE, args[ctd]), add_direction);
			parser(split_args1(args, ctd), ast, 'l');
			parser(split_args2(args, ctd), ast, 'r' );
			clean_arr_str(args);
		}
		if (flag == 2 && args[ctd])
		{
			if (ft_strncmp(args[ctd], ">", 1))
				add_full_left(ast, ast_new_node(NODE_REDIRECT_OUT, args[ctd]));
			else if (ft_strncmp(args[ctd], ">>", 2))
				add_full_left(ast, ast_new_node(NODE_REDIRECT_OUT_APPENDS, args[ctd]));
			else if (ft_strncmp(args[ctd], "<", 1))
				add_full_left(ast, ast_new_node(NODE_REDIRECT_IN, args[ctd]));
			else if (ft_strncmp(args[ctd], "<<", 2))
				add_full_left(ast, ast_new_node(NODE_REDIRECT_IN_HERE, args[ctd]));
			else
				add_full_right(ast, ast_new_node(NODE_ARGUMENT, args[ctd]));
		}
		if (!args[ctd + 1])
			flag++;
		ctd++;
	}
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
	prompt = ft_strjoin(pwd, "> Minishell$ ");
	free(pwd);
	return (prompt);
}
