#include "../includes/headers/minishell.h"

char *add_to_middle(char *src,char *to_add, int ctd, int len);

char *expander(char *str, char **env)
{

}

t_bool check_expander(char *str)
{
	int ctd;

	ctd = -1;
	while (str[++ctd])
	{
		if (str[ctd] == '$')
			return (TRUE);
	}
	return (FALSE);
}

char	*expand_1(char *str, char **env)
{
	int flag;
	int ctd;
	int len;
	char *new;
	char *var;

	ctd = -1;
	flag = 0;
	while (str[++ctd])
	{
		if (str[ctd] == '\'' && flag == 0)
			flag = 1;
		else if (str[ctd] == '\'' && flag == 1)
			flag = 0;
		if(str[ctd] == '$' && flag == 0)
		{
			len = 0;
			ctd++;
			while (ft_isalnum(str[ctd + len]))
				len++;
			new = malloc(len + 1);
			if (!new)
				return (NULL);
			ft_strncpy(new, str + ctd, len);
			var = get_env(new, env);
			if (!var)
				return (NULL);
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
	out = ft_calloc(len2, sizeof(char));
	if (!out)
		return (NULL);
	strncpy(out, src, ctd);
	ctd2 = 0;
	while (to_add[ctd2])
	{
		out[ctd + ctd2] = to_add[ctd2];
		ctd2++;
	}
	while (src[ctd + 1 + len])
	{
		out[ctd + ctd2] = src[ctd + len];
		ctd++;
		ctd2++;
	}
	return (out);
}
