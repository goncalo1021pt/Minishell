#include "../includes/headers/minishell.h"

char	*get_current_pwd()
{
	char	buffer[MAX_PATH_SIZE];
	char	*ret;
	int		i;

	i = 0;
	while (i < MAX_PATH_SIZE)
	{
		buffer[i] = 0;
		i ++;
	}
	getcwd(buffer, MAX_PATH_SIZE);
	ret = ft_strdup(buffer);
	return (ret);
}

int main (int argc, char **argv ,char **env)
{
	char	**my_env;
	char	*args[2] = {0 , 0};

	(void)argv;
	(void)argc;
	
	my_env = ft_astr_dup(env);
	print_astr(my_env);
	printf("/////////////////////////////////\n");
	ft_unset(&my_env, argv);
	ft_export(&my_env, args, 1);
	printf("/////////////////////////////////\n");
	print_astr(my_env);
	
	return (0);
}
