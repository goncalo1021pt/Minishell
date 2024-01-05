#include "../includes/headers/minishell.h"

/*
int main (int argc, char **argv ,char **env)
{
	(void)argv;
	if (argc != 1)
		return (1);
	minishell(env);
	
	return (0);
}
*/

int main (int argc, char **argv ,char **env)
{
	char	**my_env;

	(void)argv;
	if (argc != 1)
		return (1);
	
	my_env = ft_astr_dup(env);
	print_astr(my_env);
	remove_env("PATH=",&my_env);
	print_astr(my_env);
	
	return (0);
}