/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergmigu <sergmigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:26:29 by sergmigu          #+#    #+#             */
/*   Updated: 2024/02/28 14:38:07 by sergmigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <dirent.h>

# define MAX_PATH_SIZE 4096
# define TOKEN_LIST "'\"&|;<>,"
# define SPACE_LIST " \t\n\v\f\r"
# define ARGS_DIVISOR "&|<>"
# define TRUE 1
# define FALSE 0
# define ERROR -1
//ideia do fontao
# define EXIT_UNCHANGED -69420

typedef unsigned char	t_bool;

typedef enum e_signal_time
{
	ROOT,
	CHILD,
	HEREDOC,
	IGNORE,
}						t_signal_time;

typedef enum e_node_type
{
	NODE_LOGICAL,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_IN_HERE,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_OUT_APPENDS,
	NODE_REDIRECT_AMB,
	NODE_COMMAND,
	NODE_UNKNOWN,
}						t_node_type;

typedef struct s_ast_node
{
	char				*value;
	t_node_type			type;
	int					fd_in;
	int					fd_out;

	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_parser
{
	char				*str;
	t_node_type			type;
}						t_parser;

typedef struct s_info
{
	char				***env;
	t_ast_node			**tree;
}						t_info;

// main

int						minishell(char ***env);
char					*trim_path(char *path);
char					*get_prompt(void);
void					shell_level(char ***env);
t_bool					has_argument(char *str);

// lexer
char					*create_spaces(char *str);
void					create_token(char *str, int ctd, int ctd2, char *out);
char					**ft_custom_split(char *str);
char					**skip_str(char *s, char **out, int ctd);
char					**ft_split_quotes(char const *s);
void					check_null(t_list *lst);
t_bool					check_expander(char *str);
char					*expander(char *str, char **env);
void					expand_lst(t_list **lst, char **env);
char					*expand_1(char *str, char **env);
char					*handle_variable(char *str, char **env, int ctd,
							int len);
char					*expand_exit_status(char *str, int ctd);
char					*add_to_middle(char *src, char *to_add, int ctd,
							int len);
int						copy_in_quotes(char *dst, char *src, char quote_type);
char					*remove_quotes(char *str);
int						count_quotes(char *str);
int						copy_quotes(char *dst, char *src, char quote_type);
int						skip_quotes(const char *str, int ctd, char quote_type);
void					remove_quotes_lst(t_list *lst);
void					expand_wildcard(t_list **list);

// parser
t_parser				*new_parser(char *str, t_node_type type);
t_ast_node				*ast_new_node(void *c);
void					add_full_right(t_ast_node *current, t_ast_node *node);
void					add_full_left(t_ast_node *current, t_ast_node *node);
void					ast_add_node(t_ast_node *current, t_ast_node *node,
							char dir);
void					ast_free(t_ast_node *node);
void					print_tree(t_ast_node *node);
void					free_all(t_list *list);
void					print_content(void *p);
t_list					*parse_to_list(char **args);
void					free_parse_lst(void *content);
void					clean_lst(t_list *lst);
void					clean_lst(t_list *lst);
void					set_type(t_parser *parser, char **args, int ctd);
t_bool					check_syntax(t_list *lst);
t_bool					syntax_1(t_list *tmp2, t_parser *tmp2_parser,
							t_parser *parser);
t_bool					syntax_2(t_list *tmp2, t_parser *tmp2_parser,
							t_parser *parser);
void					split_redirects(t_list **lst);
void					parser_to_tree(t_list **lst, t_ast_node **ast);
void					cmd_parser(t_list *lst, t_ast_node **ast, int first);
int						search_logical(t_list *lst, t_list **nod,
							t_list **prev);
int						search_pipe(t_list *lst, t_list **nod, t_list **prev);

//wild cards

char					**get_dir_content(void);
char					*get_search(char *search);
t_bool					search_w(char *search, char *where);
char					**search_arr(char *search, char **content);
void					set_list(t_list **list, char **new);
t_list					*ft_wild(char *search, t_node_type type);

// executer
int						error_handler(int status);
int						local_exec(char **args, char **env, int fd_in,
							int fd_out);
int						path_exec(char **args, char **env, int fd_in,
							int fd_out);
int						ft_pipe(t_ast_node *node, char ***env);
int						call_process(t_ast_node *node, char ***env);
int						ft_process(t_ast_node *node, char ***env);
int						wich_logical(t_ast_node *node, char ***env);
int						ft_and(t_ast_node *node, char ***env);
int						ft_or(t_ast_node *node, char ***env);
int						ft_redirect_in(t_ast_node *node, char *fname);
int						ft_redirect_out(t_ast_node *node, char *fname);
int						ft_append_out(t_ast_node *node, char *fname);
int						ft_read_del(t_ast_node *node, char *fname);
int						ft_read_amb(char *value);
int						ft_recive_fd_in(t_ast_node *node, t_ast_node *cnode);
char					**ft_get_args(t_ast_node *node);
int						ft_get_fds(t_ast_node *node);
int						ft_get_here(t_ast_node *node);
int						ft_run(t_ast_node *node, char ***env);
int						set_fd_in(int fd_in);
int						set_fd_out(int fd_out);
int						set_fds(int fd_in, int fd_out);
void					close_fds(int fd_in, int fd_out);
int						ft_get_here_rec(t_ast_node *node);

// built_ins
int						add_env(char *new_env, char ***env);
int						change_env(char *name, char *new, char ***env);
int						remove_env(char *name, char ***env);
int						ft_cd(char **arg, char ***env);
int						ft_echo(char **arg, int fd_out);
int						ft_env(char **env, char **args, int fd_out);
void					ft_exit(int status);
void					ft_ft_exit(char **args);
t_bool					ste(char *str, char search);
int						ft_export(char ***env, char **args, int fd_out);
int						check_add(char *arg, int *ret, char ***env);
int						export_add(char *arg, char ***env);
char					*get_env_name(char *env);
int						ft_pwd(int fd_out);
int						ft_unset(char ***env, char **args);
char					*get_current_pwd(void);
char					*get_env(char *name, char **env);
char					**get_env2(char *name, char **env);

// signals
void					root_handler(int sig, siginfo_t *info, void *ucontext);
void					here_handler(int signal, siginfo_t *info,
							void *context);
void					choose_signal(t_signal_time type);
void					choose_signal2(t_signal_time type, struct sigaction sa);
void					ignore_signal(struct sigaction *sa, int signal);
int						termios_change(t_bool echo_ctl_chr);

// utils
char					**ft_astr_dup(char **astr);
char					**ft_astr_dup_add(char **astr, char *new);
char					**ft_astr_extend(char **astr, char *new);
char					**ft_astr_reduce(char **astr, size_t n_remove);
void					ft_output(char *str, int fd);
void					ft_output_nl(char *str, int fd);
void					ft_output_export(char *str, int fd);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strjoin_f1(char *s1, char const *s2);
char					*ft_strjoin_f2(char const *s1, char *s2);
char					*ft_strjoin_f12(char *s1, char *s2);
int						my_alloc(size_t size, size_t len, void **dst);
t_info					exit_info(char ***env, t_ast_node **tree);
int						err_info(int err);
void					clean_arr_str(char **astr);
void					print_arr_str(char **astr);
t_bool					is_in_array(char c, char *arr);
int						ft_arrlen(char **arr);
void					*free_arr_str(char **out, int ctd);
void					free_hd(char *fname, int mode);

#endif