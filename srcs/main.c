#include "../includes/headers/minishell.h"

int	main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)env;
	if (argc != 1)
		return (1);
	minishell(env);
	return (0);
}

/*
int main (int argc, char **argv ,char **env)
{
	char	**my_env;
	char	*null[2] = {0 , 0};

	(void)argv;
	
	my_env = ft_astr_dup(env);
	print_arr_str(my_env);
	printf("/////////////////////////////////\n");
	ft_unset(&my_env, argv);
	//change_env(NULL, "abc", &my_env);
	printf("/////////////////////////////////\n");
	print_arr_str(my_env);
	
	return (0);
}
*/

/* int	main(int argc, char **argv, char **env)
{
	char	**my_env;

	my_env = ft_astr_dup(env);
	ft_pwd(my_env, 1);
	print_arr_str(my_env);
	return(0);
} */
