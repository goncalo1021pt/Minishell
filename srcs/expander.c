#include "../includes/headers/minishell.h"

char *add_to_middle(char *src,char *to_add, int ctd, int len);
char *remove_quotes(char *str);

int	copy_in_quotes(char *dst, char *src, char quote_type)
{
	int ctd;

	ctd = 1;
	while (src[ctd] && src[ctd] != quote_type)
	{
		dst[ctd - 1] = src[ctd];
		ctd++;
	}
	return (ctd - 1);
}

char *expander(char *str, char **env)
{
	char *new;
	char *temp;

	new = str;
	while (check_expander(new))
	{
		temp = expand_1(new, env);
		if (!temp)
			return (NULL);
		free(new);
		new = temp;
	}
	temp = remove_quotes(new);
	if (!temp)
		return (NULL);
	free(new);
	new = temp;
	return (new);
}

t_bool check_expander(char *str)
{
	int ctd;

	ctd = -1;
	while (str[++ctd])
	{
		if (str[ctd] == '\'' )
			ctd = skip_quotes(str, ctd, '\'');
		if (str[ctd] == '$')
			return (TRUE);
	}
	return (FALSE);
}

char	*expand_1(char *str, char **env)
{
	int ctd;
	int len;
	char *new;
	char *var;

	ctd = -1;
	while (str[++ctd])
	{
		if (str[ctd] == '\'')
			ctd = skip_quotes(str, ctd, '\'');
		if(str[ctd] == '$')
		{
			len = 0;
			ctd++;
			while (ft_isalnum(str[ctd + len]))
				len++;
			new = ft_calloc(len + 1, sizeof(char));
			if (!new)
				return (NULL);
			ft_strncpy(new, str + ctd, len);
			var = get_env(new, env);
			str = add_to_middle(str, var, ctd - 1, len);
			if (!str)
				return (NULL);
			else
				return (str);
		}
	}
	return (str);
}

char *add_to_middle(char *src,char *to_add, int ctd, int len)
{
	char *out;
	int len2;
	int ctd2;

	len2 = ft_strlen(src) + ft_strlen(to_add) - len;
	out = ft_calloc(len2 + 1, sizeof(char));
	if (!out)
		return (NULL);
	strncpy(out, src, ctd);
	ctd2 = 0;
	while (to_add && to_add[ctd2])
	{
		out[ctd + ctd2] = to_add[ctd2];
		ctd2++;
	}
	ctd++;
	while (src[ctd + len])
	{
		out[ctd + ctd2 - 1] = src[ctd + len];
		ctd++;
	}
	return (out);
}

int count_quotes(char *str)
{
	int ctd;
	int count;

	count = 0;
	ctd = -1;
	while (str[++ctd])
	{
		if (str[ctd] == '\'' || str[ctd] == '\"')
		{
			ctd += skip_quotes(str, ctd, str[ctd]);
			count += 2;
		}
	}
	return (count);
}

char *remove_quotes(char *str)
{
	char *out;
	int ctd;
	int ctd2;
	int copied;

	out = ft_calloc(ft_strlen(str) - count_quotes(str) + 1, sizeof(char));
	if (!out)
		return (NULL);
	ctd = 0;
	ctd2 = 0;
	while (str[ctd])
	{
		if (str[ctd] == '\'' || str[ctd] == '\"')
		{
			copied = copy_in_quotes(out + ctd2, str + ctd, str[ctd]);
			ctd2 += copied;
			ctd += copied + 2;
		}
		else
			out[ctd2++] = str[ctd++];
	}
	return (out);
}
