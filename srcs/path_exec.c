#include "../includes/headers/minishell.h"

static int	test_path(char *path, char *pname)
{
	char	*aux;

	aux = ft_strjoin_f1(ft_strjoin(path, "/"), pname);
	if (access(aux, F_OK) == 0)
	{
		free(aux);
		return (1);
	}
	else
	{
		free(aux);
		return (-1);
	}
}

static char	*find_env_paths(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
			return (env[i]);
		i++;
	}
	return (NULL);
}

static char	*find_path(char *pname, char **env)
{
	char	*paths;
	char	**path_ar;
	char	*ret;
	int		i;

	paths = find_env_paths(env);
	if (!paths)
		return (NULL);
	path_ar = ft_split(paths, ':');
	if (!path_ar)
		return (NULL);
	i = 1;
	ret = NULL;
	while (path_ar[i])
	{
		if (test_path(path_ar[i], pname) == 1)
		{
			ret = ft_strjoin_f1(ft_strjoin(path_ar[i], "/"), pname);
			break ;
		}
		i++;
	}
	clean_arr_str(path_ar);
	return (ret);
}
void    path_exec(char **args, char **env, int fd_in, int fd_out)
{
	char	*path;

	path = find_path(args[0], env);
	if (!path)
	{
		ft_output(args[0], STDERR_FILENO);
		ft_output_nl(": command not found", STDERR_FILENO);
		ft_exit(127);
	}
	if (set_fds(fd_in, fd_out) == -1 || execve(path, args, env) == -1)
	{
		perror(args[0]);
		free(path);
		ft_exit(errno);
	}
	free(path);
	close_fds(fd_in, fd_out);
    ft_exit(errno);
}

/*
int    path_exec(char **args, char **env, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = find_path(args[0], env);
	if (!path)
	{
		ft_output(args[0], STDERR_FILENO);
		ft_output_nl(": command not found", STDERR_FILENO);
		return (1);
	}
	choose_signal(IGNORE);
	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		choose_signal(CHILD);
		if (set_fds(fd_in, fd_out) == -1 || execve(path, args, env) == -1)
		{
			perror(args[0]);
			ft_exit(0);
		}
	}
	close_fds(fd_in, fd_out);
	waitpid(pid, &status, 0);
	free(path);
    return (status);
}
*/
/*
int	main(int argc, char **argv, char **env)
{
	int	fd;

	fd = open("teste", O_RDONLY);
    if (argv[1])
	    path_exec(&argv[1], env, fd, STDOUT_FILENO);
	close (fd);
	return (0);
}
*/
