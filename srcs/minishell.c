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

char **split_args2(char **args, int ctd)
{
	char	**new_args;
	int		ctd2;

	ctd2 = 0;
	new_args = malloc(sizeof(char *) * (ctd + 1));
	while (args[ctd])
	{
		new_args[ctd2] = ft_strdup(args[ctd]);
		ctd2++;
		ctd++;
	}
	new_args[ctd2] = NULL;
	return (new_args);
}

// ls -l && echo "hard big of shit" || echo bye world

void parser(char **args, t_ast_node *ast, char add_direction)
{
	int			ctd;

	ctd = 0;
	while (args[ctd])
	{
		if (args[ctd] && ft_strncmp(args[ctd], "||", 2) || ft_strncmp(args[ctd], "&&", 2))
		{
			ast_add_node(ast, ast_new_node(NODE_LOGICAL, args[ctd]), add_direction);
			parser(split_args1(args, ctd), ast, 'l');
			parser(split_args2(args, ctd), ast, 'l' );
			break;
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
