#include "../../includes/headers/minishell.h"

char	*expand_1(char *str, char **env)
{
	int	ctd;
	int	len;

	ctd = -1;
	while (str[++ctd])
	{
		if (str[ctd] == '\'')
			ctd = skip_quotes(str, ctd, '\'');
		if (str[ctd] == '$')
		{
			len = 0;
			ctd++;
			if (str[ctd] == '?')
				return (expand_exit_status(str, ctd));
			while (ft_isalnum(str[ctd + len]))
				len++;
			return (handle_variable(str, env, ctd, len));
		}
	}
	return (str);
}

char	*handle_variable(char *str, char **env, int ctd, int len)
{
	char	*new;
	char	*var;

	new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_strncpy(new, str + ctd, len);
	var = get_env(new, env);
	free(new);
	str = add_to_middle(str, var, ctd - 1, len);
	if (!str)
		return (NULL);
	else
		return (str);
}

char	*expand_exit_status(char *str, int ctd)
{
	char	*new;
	char	*status;

	status = ft_itoa(err_info(EXIT_UNCHANGED));
	if (!status)
		return (NULL);
	new = ft_calloc(ft_strlen(str) + ft_strlen(status) - 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_strncpy(new, str, ctd - 1);
	ft_strncpy(new + ctd - 1, status, ft_strlen(status));
	ft_strncpy(new + ctd - 1 + ft_strlen(status), str + ctd + 1, ft_strlen(str)
			- ctd - 1);
	free(status);
	return (new);
}
