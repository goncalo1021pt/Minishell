/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:46 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/26 16:52:06 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

void	free_all(t_list *list)
{
	ft_lstclear(&list, free_parse_lst);
}

void	print_content(void *p)
{
	t_parser	*parser;

	parser = p;
	ft_printf("String: %s, Type: %d\n", parser->str, parser->type);
}

void	free_parse_lst(void *content)
{
	t_parser	*parser;

	parser = content;
	if (parser->str)
		free(parser->str);
	free(parser);
}

void	clean_lst(t_list *lst)
{
	if (lst)
	{
		clean_lst(lst->next);
		if (lst->content)
		{
			if (((t_parser *)(lst->content))->str)
				free(((t_parser *)(lst->content))->str);
			free((t_parser *)(lst->content));
		}
		free(lst);
	}
}
