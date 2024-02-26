#include "../../includes/headers/minishell.h"

char	**get_dir_content()
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
	return(ret);
}

char	*get_search(char *search)
{
	size_t	i;
	char	*str;

	i = 0;
	while(search[i] && search[i] != '*')
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
	return(str);
}

t_bool	search_w(char *search, char *where)
{
	char	*aux;
	size_t	i;

	i = 0;
	while (1)
	{
		if (search[i] == '\0')
			return(TRUE);
		if (search[i] == '*')
		{
			i++;
			aux = get_search(&search[i]);
			where = ft_strnstr(where, aux , ft_strlen(where));
			i += ft_strlen(aux);
			if (!where || (!search[i] && ft_strncmp(aux, &where[ft_strlen(where) - ft_strlen(aux)], ft_strlen(aux))))
			{
				free(aux);
				return(FALSE);
			}
			free(aux);
		}
		else
		{
			aux = get_search(&search[i]);
			if (ft_strncmp(aux, where, ft_strlen(aux)))
			{
				free(aux);
				return (FALSE);
			}
			i += ft_strlen(aux);
			free(aux);
		}
	}
}

char	**search_arr(char *search, char **content)
{
	char	**ret;
	char	**aux;
	size_t	i;

	ret = NULL;
	i = 0;
	while(content[i])
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

void	set_list(t_list **list, char **new)
{
	size_t		i;
	t_parser	*content;
	t_list		*node;

	i = 0;
	while(new[i])
	{
		content = (t_parser *)malloc(sizeof(t_parser));
		if (content)
		{
			node = (t_list *)malloc(sizeof(t_list));
			if (!node)
			{
				free(content);
				free(new[i]);
			}
			else
			{
				content->str = new[i];
				content->type = NODE_COMMAND;
				node->content = content;
				ft_lstadd_back(list, node);
			}
		}
		else
			free(new[i]);
		i++;
	}
	free(new);
}

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


t_list	*ft_wild(t_list **list)
{
	char	**content;
	char	**ret;
	char	*search;
	t_list	*lst_aux;

	ft_lstiter(*list, print_content);
	lst_aux = NULL;
	search = ((t_parser *)((*list)->content))->str;
	if (!search)
		return (*list);
	content = get_dir_content();
	ret = search_arr(search, content);
	free(content);
	if (ret)
	{
		set_list(&lst_aux, ret);
		ft_lstiter(lst_aux, print_content);
		ft_lstiter(lst_aux, print_content);
		return(lst_aux);
	}
	else
		return(*list);
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
