/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:08 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/27 12:47:09 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

void	expand_lst(t_list **lst, char **env)
{
	t_parser	*content;
	t_list		*start;

	start = *lst;
	while (start != NULL)
	{
		content = start->content;
		if (content->type != NODE_REDIRECT_IN_HERE)
			content->str = expander(content->str, env);
		start = start->next;
	}
	expand_wildcard(lst);
	remove_quotes_lst(*lst);
}

char	*expander(char *str, char **env)
{
	char	*new;
	char	*temp;

	new = str;
	
	while (check_expander(new))
	{
		temp = expand_1(new, env);
		if (!temp)
			return (free(new), NULL);
		free(new);	
		new = temp;
	}
	if (new[0] == '\0')
	{
		free(new);
		return (NULL);
	}
	return (new);
}

t_bool	check_expander(char *str)
{
	int		ctd;
	t_bool	flag;

	ctd = -1;
	flag = TRUE;
	while (str[++ctd])
	{
		if (str[ctd] == '\"')
			flag = !flag;
		if (flag && str[ctd] == '\'')
			ctd = skip_quotes(str, ctd, '\'');
		if (str[ctd] == '$' && (ft_isalnum(str[ctd + 1]) || str[ctd
					+ 1] == '?'))
			return (TRUE);
	}
	return (FALSE);
}

void	check_null(t_list *lst)
{
	t_parser	*content;

	while (lst != NULL)
	{
		content = lst->content;
		if (content->str && content->str[0] == '\0')
		{
			free(content->str);
			content->str = NULL;
		}
		lst = lst->next;
	}
}
