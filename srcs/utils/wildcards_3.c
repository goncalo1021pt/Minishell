/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:57:27 by gfontao-          #+#    #+#             */
/*   Updated: 2024/02/27 18:06:42 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

char	**search_arr(char *search, char **content)
{
	char	**ret;
	char	**aux;
	size_t	i;

	ret = NULL;
	i = 0;
	while (content[i])
	{
		if (!(content[i][0] == '.') && search_w(search, content[i]))
		{
			aux = ft_astr_extend(ret, content[i]);
			if (ret)
				free(ret);
			ret = aux;
		}
		else
			free(content[i]);
		i++;
	}
	return (ret);
}

static void	set_list_aux(t_list **list, char **new, int i)
{
	t_parser	*content;
	t_list		*node;

	node = NULL;
	content = NULL;
	content = (t_parser *)malloc(sizeof(t_parser));
	if (content)
	{
		node = ft_lstnew(content);
		if (!node)
		{
			free(content);
			free(new[i]);
		}
		else
		{
			content->str = new[i];
			content->type = NODE_COMMAND;
			ft_lstadd_back(list, node);
		}
	}
	else
		free(new[i]);
}

void	set_list(t_list **list, char **new)
{
	size_t	i;

	i = 0;
	while (new[i])
	{
		set_list_aux(list, new, i);
		i++;
	}
	free(new);
}
