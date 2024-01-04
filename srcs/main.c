#include "../includes/headers/minishell.h"

int main (int argc, char **argv ,char **env)
{
	(void)argv;
	if (argc != 1)
		return (1);
	minishell(env);
	
	return (0);
}
