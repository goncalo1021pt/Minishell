#include "../includes/headers/minishell.h"

int	minishell(char **env)
{
	t_shell_list	shell;
	char			*line;
	char 			**args;
	char			*promt;

	(void)env;
	(void)shell;
	//root_signals();
	while (1)
	{
		promt = get_prompt();
		line = readline(promt);
		if (!line)
			exit(0);
		if (line[0] != '\0')
			add_history(line);
		shell.args = ft_split_quotes(line, ' ');
		print_arr_str(shell.args);
		free(promt);
		free(line);
		if (shell.args[0] != NULL)
			clean_arr_str(shell.args);
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
