#include "../includes/headers/minishell.h"

static int	change_dir(char *path, char ***env)
{
	if (!path)
		return (1);
	if (chdir(path) == 0)
	{
		if (get_env("PWD", *env))
		{
			change_env("OLDPWD", ft_str_join("OLDPWD", get_env("PWD", env), env));
			change_env("PWD", ft_strjoin_f2("PWD", get_current_pwd()), env);
		}
		return (0);
	}
	else
		return (-1);
}


int	ft_cd(char **arg, char ***env)

{
	char	*where;

	where == NULL;
	if (!arg)
		return (1);
	else if (!(arg[1]) || (ft_strlen(arg[1]) == 1 && arg[1][1] == '~'))
	{
		where = get_env("HOME", *env);
		if (!where)
		{
			ft_output_nl("cd: HOME not set", STDERR_FILENO);
			return (2);
		}
	}
	else if (ft_strlen(arg) == 1 && *arg == '-')
	{
		where = get_env("OLDPWD", *env);
		if (where)
			ft_output_nl(where);
		else
		{
			ft_output_nl("cd: OLDPWD not set", STDERR_FILENO);
			return (3);
		}
	}
	else
		where = arg;
	return (change_dir(where, env));
}