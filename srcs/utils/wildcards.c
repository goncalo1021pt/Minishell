/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 17:52:20 by gfontao-          #+#    #+#             */
/*   Updated: 2024/02/27 18:05:38 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

t_list	*ft_wild_arg(char *search)
{
	char	**content;
	char	**ret;
	t_list	*lst_aux;

	lst_aux = NULL;
	if (!search)
		return (NULL);
	content = get_dir_content();
	ret = search_arr(search, content);
	free(content);
	if (ret)
	{
		set_list(&lst_aux, ret);
		return (lst_aux);
	}
	else
		return (NULL);
}

t_parser	*new_parser(char *str, t_node_type type)
{
	t_parser	*aux;

	aux = (t_parser *)malloc(sizeof(t_parser));
	if (!aux)
		return (NULL);
	aux->str = str;
	aux->type = type;
	return (aux);
}

t_list	*ft_wild_red(char *search, t_node_type type)
{
	char	**content;
	char	**ret;
	t_list	*lst_aux;

	lst_aux = NULL;
	if (!search)
		return (NULL);
	content = get_dir_content();
	ret = search_arr(search, content);
	free(content);
	if (ret && ret[0])
	{
		if (ret[1])
		{
			lst_aux = ft_lstnew(new_parser(ft_strdup(search),
						NODE_REDIRECT_AMB));
		}
		else
		{
			lst_aux = ft_lstnew(new_parser(ft_strdup(ret[0]), type));
		}
		return (clean_arr_str(ret), lst_aux);
	}
	return (NULL);
}

t_list	*ft_wild(char *search, t_node_type type)
{
	if (type == NODE_COMMAND)
	{
		return (ft_wild_arg(search));
	}
	else
	{
		return (ft_wild_red(search, type));
	}
}

/*
char	*ft_wild(char *search)
{
	char	**content;
	char	**ret;

	if (!search)
		return (NULL);
	content = get_dir_content();
	ret = search_arr(search, content);
	free(content);
	if (ret)
		return (reverse_split(ret));
	else
		return (ft_strdup(search));
	return (NULL);
}
*/

/*
void	add_list(t_list **list, t_list **add)
{
	t_list	**aux;

	if (!list || !(*list) || !add || !(*add))
	{
		clean_lst(*add);
		return ;
	}
	aux = add;
	while(*aux)
	{
		*aux = (*aux)->next;
	}
	*aux = (*list)->next;
	del_node(*list);
}
*/

/*
char*	reverse_split(char **elm)
{
	size_t	i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (elm[i])
	{
		if (ret)
			ret = ft_strjoin_f1(ret, " ");
		ret = ft_strjoin_f1(ret, elm[i]);
		i++;
	}
	clean_arr_str(elm);
	return (ret);
}
*/

/*
static void	del_node(t_list *lst)
{
	if (lst)
	{
		if (lst->content)
		{
			if (((t_parser *)(lst->content))->str)
				free(((t_parser *)(lst->content))->str);
			free((t_parser *)(lst->content));
		}
		free(lst);
	}
}
*/