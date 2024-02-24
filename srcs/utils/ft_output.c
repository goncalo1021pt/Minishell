/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:29:09 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/24 15:10:27 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

void	ft_output(char *str, int fd)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		write(fd, &(str[i]), 1);
		i++;
	}
}

void	ft_output_nl(char *str, int fd)
{
	ft_output(str, fd);
	write(fd, "\n", 1);
}

void	ft_output_export(char *str, int fd)
{
	size_t	i;
	int		check;

	i = 0;
	check = 0;
	while (str[i])
	{
		write(fd, &(str[i]), 1);
		if (check == 0 && str[i] == '=')
		{
			write(fd, "\"", 1);
			check = 1;
		}
		i++;
	}
	if (check == 1)
		write(fd, "\"", 1);
	write(fd, "\n", 1);
}
