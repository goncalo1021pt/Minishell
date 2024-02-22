/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfontao- <gfontao-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:28:27 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/22 18:39:56 by gfontao-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/headers/minishell.h"

static char	*minishell_aux_1(void)
{
	char	*promt;
	char	*line;

	promt = get_prompt();
	termios_change(FALSE);
	line = readline(promt);
	termios_change(TRUE);
	free(promt);
	return (line);
}

static t_list	*minishell_aux_2(char *line)
{
	char	**args;
	t_list	*list;

	if (line[0] != '\0')
		add_history(line);
	args = ft_custom_split(line);
	free(line);
	if (!args)
		return (NULL);
	list = parse_to_list(args);
	clean_arr_str(args);
	return (list);
}

static t_bool	confirm_free(char *line)
{
	free(line);
	return (TRUE);
}

static t_bool	display_error(t_list *list)
{
	ft_putendl_fd("syntax error", 2);
	err_info(2);
	free_all(list);
	return (TRUE);
}

int	minishell(char ***env)
{
	char		*line;
	t_ast_node	*ast;
	t_list		*list;

	exit_info(env, &ast);
	while (1)
	{
		choose_signal(ROOT);
		ast = NULL;
		line = minishell_aux_1();
		if (!line)
			ft_exit(0);
		if (!*line || has_argument(line))
		{
			confirm_free(line);
			continue ;
		}
		list = minishell_aux_2(line);
		if (!list || (!check_syntax(list) && display_error(list)))
			continue ;
		expand_lst(list, *env);
		parser_to_tree(&list, &ast);
		err_info(call_process(ast, env));
		ast_free(ast);
	}
}
