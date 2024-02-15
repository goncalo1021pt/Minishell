#include "../includes/headers/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	**my_env;

	(void)argv;
	if (argc != 1)
		return (1);
	my_env = ft_astr_dup(env);
	minishell(&my_env);
	return (0);
}
