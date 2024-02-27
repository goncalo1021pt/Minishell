/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:55:51 by gfontao-          #+#    #+#             */
/*   Updated: 2024/02/27 18:07:40 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

char	**get_dir_content(void)
{
	DIR				*dir;
	struct dirent	*read;
	char			**ret;
	char			**aux;
	char			*path;

	ret = NULL;
	path = get_current_pwd();
	if (!path)
		return (NULL);
	dir = opendir(path);
	free(path);
	if (!dir)
		return (NULL);
	read = readdir(dir);
	while (read)
	{
		aux = ft_astr_extend(ret, ft_strdup(read->d_name));
		if (ret)
			free(ret);
		ret = aux;
		read = readdir(dir);
	}
	closedir(dir);
	return (ret);
}

char	*get_search(char *search)
{
	size_t	i;
	char	*str;

	i = 0;
	while (search[i] && search[i] != '*')
	{
		i++;
	}
	if (my_alloc(sizeof(char), i + 1, (void **)(&str)))
		return (NULL);
	while (i > 0)
	{
		i--;
		str[i] = search[i];
	}
	return (str);
}

static t_bool	searc_w_aux(char *search, char *where, size_t *i)
{
	char	*aux;

	*i = *i + 1;
	aux = get_search(&search[*i]);
	where = ft_strnstr(where, aux, ft_strlen(where));
	*i += ft_strlen(aux);
	if (!where || (!search[*i] && ft_strncmp(aux, &where[ft_strlen(where)
					- ft_strlen(aux)], ft_strlen(aux))))
	{
		free(aux);
		return (FALSE);
	}
	free(aux);
	return (TRUE);
}

static t_bool	searc_w_aux_2(char *search, char *where, size_t *i)
{
	char	*aux;

	aux = get_search(&search[*i]);
	if (ft_strncmp(aux, where, ft_strlen(aux)))
	{
		free(aux);
		return (FALSE);
	}
	*i += ft_strlen(aux);
	free(aux);
	return (TRUE);
}

t_bool	search_w(char *search, char *where)
{
	size_t	i;

	i = 0;
	while (1)
	{
		if (search[i] == '\0')
			return (TRUE);
		if (search[i] == '*')
		{
			if (!searc_w_aux(search, where, &i))
				return (FALSE);
		}
		else
		{
			if (!searc_w_aux_2(search, where, &i))
				return (FALSE);
		}
	}
}
