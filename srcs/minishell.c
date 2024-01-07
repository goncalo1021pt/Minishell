#include "../includes/headers/minishell.h"

int	minishell(char **env)
{
	t_shell_list	*shell;

	(void)env;
	shell = NULL;
	change_signals();
	while (1)
	{
		display_prompt();
		read_input(shell);
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

void	display_prompt(void)
{
	char	*pwd;

	pwd = get_current_pwd();
	pwd = trim_path(pwd);
	ft_printf("%s> Minishell$ ", pwd);
	free(pwd);
}
