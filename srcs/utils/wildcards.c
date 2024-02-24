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
		return (search);
	return (NULL);
}
