#include "../includes/headers/minishell.h"

int	main(int argc, char **argv, char **env)
{
	// char	**my_env;

	(void)argv;
	(void)env;
	if (argc != 1)
		return (1);
	// my_env = ft_astr_dup(env);
	// minishell(&my_env);
	char *str;
	char *str2;

	str = ft_strdup("echo $USER");
	str2 = ft_strdup("echo $USER");
	printf("str: %s\n", str);
	printf("str2: %s\n", str2);
	expand(str, env);
	printf("str: %s\n", str);
	printf("str2: %s\n", str2);
	return (0);
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
