#include "../includes/headers/minishell.h"

static char	*get_home_dir(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("HOME=", env[i], 5) == 0)
			return (&env[i][5]);
		i++;
	}
	return (NULL);
}

static char	*get_old_dir(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("OLDPWD=", env[i], 7) == 0)
			return (&env[i][7]);
		i++;
	}
	return (NULL);
}

static char	*get_current_dir(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PWD=", env[i], 4) == 0)
			return (&env[i][4]);
		i++;
	}
	return (NULL);
}

int	change_dir(char *path, char **env)
{
	if (!path)
		return (1);
	if (chdir(path) == 0)
	{
		change_env("OLDPWD=", get_env("PWD=", env), &env);
		change_env("PWD=", path, &env);
		return (0);
	}
	else
		return (-1);
}

int	my_cd(char *arg, char **env)

{
	char	*where;

	if (!arg)
		return (1);
	else if (!(*arg) || (ft_strlen(arg) == 1 && *arg == '~'))
		where = get_home_dir(env);
	else if (ft_strlen(arg) == 1 && *arg == '-')
	{
		where = get_old_dir(env);
		printf("%s\n", where);
	}
	else
		where = arg;
	return (change_dir(where, env));
}
