#include "../includes/headers/minishell.h"

int	minishell(char **env)
{
	t_shell_list	*shell;

	(void)env;
	shell = NULL;
	change_signals();
	while (1)
	{
		read_input(shell, get_prompt());
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


