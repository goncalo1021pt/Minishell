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
	char	*null[2] = {0 , 0};

	(void)argv;
	
	my_env = ft_astr_dup(env);
	print_astr(my_env);
	printf("/////////////////////////////////\n");
	ft_export(&my_env, argv);
	//change_env(NULL, "abc", &my_env);
	printf("/////////////////////////////////\n");
	print_astr(my_env);
	printf("/////////////////////////////////\n");
	ft_export(&my_env, null);
	
	return (0);
}