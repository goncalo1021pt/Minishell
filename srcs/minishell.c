#include "../includes/headers/minishell.h"

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
			exit(0);
		if (line[0] != '\0')
			add_history(line);
		args = ft_split_quotes(line, ' ');
		print_arr_str(args);
		free(promt);
		free(line);
		clean_arr_str(args);
	}
}

void parser(char **args, t_ast_node *ast)
{
	int			ctd;
	t_ast_node	*temp;
	ctd = 0;
	while (args[ctd])
	{
		if (args[ctd] && ft_strncmp(args[ctd], "||", 2) || ft_strncmp(args[ctd], "&&", 2))
		{
			ast_add_node(ast, ast_new_node(NODE_LOGICAL, args[ctd]), 'r');
			if (ast->right)
				temp = ast->right;
			parser(new_args(args, ctd), temp); 
		}
	}
	clean_arr_str(args);
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
