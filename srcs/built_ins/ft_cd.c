#include "../../includes/headers/minishell.h"
#define PWD_MSG "minishell: cd: OLDPWD not set"

static int	change_dir(char *path, char ***env)
{
	if (!path)
		return (1);
	if (chdir(path) == 0)
	{
		if (get_env("PWD", *env))
		{
			change_env("OLDPWD",
				ft_strjoin("OLDPWD=", get_env("PWD", *env)),
				env);
			change_env("PWD", ft_strjoin_f2("PWD=", get_current_pwd()), env);
		}
		return (0);
	}
	else
	{
		ft_output("minishell: cd: no such directory: ", STDOUT_FILENO);
		ft_output_nl(path, STDOUT_FILENO);
		return (1);
	}
}

int	ft_cd(char **arg, char ***env)
{
	char	*where;

	where = NULL;
	if (!arg)
		return (1);
	else if (!(arg[1]) || (ft_strlen(arg[1]) == 1 && arg[1][0] == '~'))
	{
		where = get_env("HOME", *env);
		if (!where)
		{
			ft_output_nl("minishell: cd: HOME not set", STDERR_FILENO);
			return (1);
		}
	}
	else if (ft_strlen(arg[1]) == 1 && arg[1][0] == '-')
	{
		where = get_env("OLDPWD", *env);
		if (where)
			ft_output_nl(where, STDOUT_FILENO);
		else
			return (ft_output_nl(PWD_MSG, STDERR_FILENO), 3);
	}
	else
		where = arg[1];
	return (change_dir(where, env));
}