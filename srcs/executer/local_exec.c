/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:27:35 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/22 17:55:52 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

static void	local_exec_aux(char **args, char **env, int fd_in, int fd_out)
{
	char	*mess;

	if (access(args[0], F_OK) != 0)
	{
		mess = ft_strjoin("minishell: ", args[0]);
		perror(mess);
		free(args);
		free(mess);
		ft_exit(127);
	}
	if (set_fds(fd_in, fd_out) == -1 || execve(args[0], args, env) == -1)
	{
		mess = ft_strjoin("minishell: ", args[0]);
		perror(mess);
		free(args);
		free(mess);
		ft_exit(126);
	}
	close_fds(fd_in, fd_out);
	ft_exit(errno);
}

static void	is_dir(char **args)
{
	DIR	*dir;

	dir = opendir(args[0]);
	if (dir)
	{
		closedir(dir);
		ft_output("minishell: ", STDERR_FILENO);
		ft_output(args[0], STDERR_FILENO);
		ft_output_nl(": Is a directory", STDERR_FILENO);
		free(args);
		ft_exit(126);
	}
}

int	local_exec(char **args, char **env, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	choose_signal(IGNORE);
	pid = fork();
	if (pid < 0)
	{
		perror("minishel:");
		return (errno);
	}
	else if (pid == 0)
	{
		choose_signal(CHILD);
		is_dir(args);
		local_exec_aux(args, env, fd_in, fd_out);
	}
	close_fds(fd_in, fd_out);
	waitpid(pid, &status, 0);
	status = error_handler(status);
	return (status);
}

int	error_handler(int status)
{
	if (status == 0)
	{
		err_info(0);
		return (status);
	}
	else
		err_info(128 + status);
	if (status == 2)
	{
		status = 130;
		ft_printf("\n");
	}
	else if (status == 131)
		ft_printf("Quit\n");
	if (status > 255)
		status = status / 256;
	status = err_info(status);
	return (status);
}
