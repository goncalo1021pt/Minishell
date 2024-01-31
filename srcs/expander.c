#include "../includes/headers/minishell.h"

t_bool check_expander(char *str)
{
	int ctd;

	ctd = 0;
	while (str[ctd])
	{
		if (str[ctd] == '$')
			ctd++;
	}
	return (FALSE);
}

t_bool expand(char *str, char **env)
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
		if(str[ctd] == '$' && flag == 1)
		{
			len = 0;
			while (ft_isalnum(str[ctd + len]))
				len++;
			new = malloc(len);
			if (!new)
				return NULL;
			ft_strlcat(new, str + ctd, len);
			var = get_env(new, env);
			
		}
	}
	return (FALSE);
}

char *add_to_middle(char *src,char *to_add, int ctd)
{
	char *out;
	int ctd2;

	ctd2 = 0;
	while (ctd2 < ctd)
	{
		
		ctd++;
	}
}