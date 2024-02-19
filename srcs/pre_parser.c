#include "../includes/headers/minishell.h"

char	**get_par(char *prompt)
{
	size_t	i;
	size_t	j;
	char	**ret;

	i = 0;
	ret = NULL;
	while (prompt && prompt[i])
	{
		if (prompt[i] == '\'' || prompt[i] == '\"')
			skip_quotes(prompt, i, prompt[i]);
		if (prompt[i] == '(')
		{
			j = 0;
			i ++;
			while (prompt[i + j] != ')')
			{
				if (!prompt[i + j])
				{
					clean_arr_str(ret);
					return(NULL);
				}	
				j ++;
			}
			add_env(ft_substr(prompt, i, j), &ret);
			i = i + j;
		}
		else if (prompt[i] == ')')
		{
			clean_arr_str(ret);
			return(NULL);
		}
		if (prompt[i])
			break ;
		i++;
	}
	return (ret);
}

char	*add_prompt(char *prompt, char *add, size_t *j)
{
	size_t	i;
	char	*ret;

	ret = NULL;
	while (prompt[*j])
	{
		if (prompt[*j] == '\'' || prompt[*j] == '\"')
			skip_quotes(prompt, *j, prompt[*j]);
		if (prompt[*j] == '(')
		{
			i = 0;
			while (prompt[i + *j] != ')')
			{
				i++;
			}
			ret = ft_strjoin_f12(ft_substr(prompt, 0, *j), add);
			(*j)++;
			ret = ft_strjoin_f1(ret, &(prompt[*j + i]));
			free(prompt);
			break;
		}
		if (prompt[*j])
			break ;
		(*j)++;
	}
	return (ret);
}


void	one_cicle(char *line, char ***env, int fd_out)
{
	char 			**args;
	t_ast_node		*ast;
	t_list			*list;

	set_fds(STDIN_FILENO, fd_out);
	exit_info(env, &ast);
	choose_signal(ROOT);
	ast = NULL;
	list = NULL;
	termios_change(FALSE);
	termios_change(TRUE);
	if (line[0] != '\0')
		add_history(line);
	args = ft_custom_split(line);
	free(line);
	list = parse_to_list(args);
	clean_arr_str(args);
	if (!check_syntax(list))
	{
		ft_putendl_fd("syntax error", 2);
		err_info(2);
		free_all(list);
		ft_exit(0);
	}
	expand_lst(list, *env);
	parser(&list, &ast);
	err_info(call_process(ast, env));
	ast_free(ast);
}

static char	*pseudo_pipe(int pip[2], int fk1)
{
	char	*ret;
	char	*line;

	close(pip[1]);
	line = get_next_line(pip[0]);
	ret = NULL;
	while (line)
	{
		if (!ret)
			ret = line;
		else
			ret = ft_strjoin_f12(ret, line);
		line = get_next_line(pip[0]);
	}
	close(pip[0]);
	waitpid(fk1, NULL, 0);
	return (ret);
}

char	*get_out_min(char *text, char ***env)
{
	int		pip[2];
	int		fk1;

	if (pipe(pip) == -1)
	{
		perror("minishell: ");
		ft_exit(errno);
	}
	fk1 = fork();
	if (fk1 < 0)
	{
		perror("minishell: ");
		ft_exit (errno);
	}
	if (fk1 == 0)
	{
		close(pip[0]);
		one_cicle(text, env , pip[1]);
		ft_exit(0);
	}
	return (pseudo_pipe(pip, fk1));
}

char	*pre_parser(char *prompt, char ***env)
{
	char	**pre_run;
	char	*ret;
	char	*aux;
	size_t	i;
	size_t	j;

	pre_run = get_par(prompt);
	i = 0;
	j = 0;
	ret = prompt;
	while (pre_run && pre_run[i])
	{
		aux = get_out_min(pre_run[i], env);
		ret = add_prompt(ret, aux, &j);
		i++;
	}
	printf("FINAL PROMT :: %s\n", ret);
	return (ret);
}