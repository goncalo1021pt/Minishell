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
# include <unistd.h>

# define MAX_PATH_SIZE 4096
# define TOKEN_LIST "'\"&|;<>,"
# define SPACE_LIST " \t\n\v\f\r"
# define ARGS_DIVISOR "&|<>"
# define TRUE 1
# define FALSE 0

typedef unsigned char	t_bool;


// typedef struct s_args 
// {
// 	char *str;
// 	struct s_args *next;

// } t_args



typedef enum e_node_type
{
	NODE_LOGICAL,
	NODE_PIPE,
	NODE_COMMAND,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_IN_HERE,
	NODE_REDIRECT_OUT,
	NODE_REDIRECT_OUT_APPENDS,
	NODE_ARGUMENT,
	NODE_UNKNOWN,
}						t_node_type;

typedef struct s_ast_node
{
	char				*value;
	t_node_type			type;
	// char				**args;
	int					fd_in;
	int					fd_out;
	
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	// struct s_ast_node	*parent;
}						t_ast_node;

typedef struct s_parser
{
	char				*str;
	t_node_type			type;
}						t_parser;

// typedef struct s_shell_list
// {
// 	int					cmd_id;
// 	// t_args				*args;
// 	char				**args;
// 	int					conex;
// 	int					fd_in;
// 	char				*file_in;
// 	char				*file_out;

// 	struct s_shell_list	*next;
// 	struct s_shell_list	*prev;
// }						t_shell_list;


// core

int						minishell(char **env);
char					*get_prompt(void);

char					*get_current_pwd(void);

//strings

size_t					ft_strlen(char const *str);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strjoin_f1(char *s1, char const *s2);
char					*ft_strjoin_f2(char const *s1, char *s2);
char					*ft_strjoin_f12(char *s1, char *s2);
char					**ft_split(char const *s, char c);
char					*ft_strdup(const char *str);
void					clean_arr_str(char **astr);
char					**ft_astr_dup(char **astr);
char					**ft_astr_dup_add(char **astr, char *nw);
char					**ft_astr_extend(char **astr, char *nw);
char					**ft_astr_reduce(char **astr, size_t n_remove);
void					print_arr_str(char **astr);
char					*ft_strchr(const char *str, int c);
char					**ft_split_quotes(char const *s);
char					**ft_costume_split(char *str);
char 					*create_spaces(char *str);
t_bool					is_in_array(char c, char *arr);

// numeric

// long					ft_atoi(char *str);

// memory

int						my_alloc(size_t size, size_t len, void **dst);

// lists

// t_shell_list			new_node(int id, char **args, int conex);
// void					set_node_fds(int fd_in, int fd_out, char file_in);
// void					clean_list(t_shell_list **begining);

// env

char					*get_env(char *name, char **env);
char					**get_env2(char *name, char **env);
int						remove_env(char *name, char ***env);
int						add_env(char *new_env, char ***env);
int						change_env(char *name, char *new_env, char ***env);
char					*get_env_name(char *env);

// execs

int						path_exec(char **args, char **env, int fd_in,
							int fd_out);
int						local_exec(char **args, char **env, int fd_in,
							int fd_out);

// built ins

int						ft_echo(char *arg, char **env);
int						ft_cd(char **arg, char ***env);
int						ft_pwd(int fd_out);
int						ft_env(char **env, char **args, int fd_out);
int						ft_export(char ***env, char **args, int fd_out);
int						ft_unset(char ***env, char **args);
void					ft_exit(int status);

// ast

t_ast_node				*ast_new_node(t_node_type type, char *value);
void					ast_add_node(t_ast_node *current, t_ast_node *node,
							char dir);
void					add_full_right(t_ast_node *current, t_ast_node *node);
void					add_full_left(t_ast_node *current, t_ast_node *node);
void					ast_free(t_ast_node *node);
void					ast_print(t_ast_node *node);



// fds

int						set_fd_in(int fd_in);
int						set_fd_out(int fd_out);
int						set_fds(int fd_in, int fd_out);

// output

void					ft_output(char *str, int fd);
void					ft_output_nl(char *str, int fd);

// signals

void					root_signals(void);
void					signal_handler(int signal, siginfo_t *info,
							void *context);
void					ignore_signal(struct sigaction *sa, int signal);

// pharsing


// list execution

// ft_exit

int						minishell_exit(void);

#endif