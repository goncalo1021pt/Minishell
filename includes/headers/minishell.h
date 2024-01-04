#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef struct s_shell_list
{
	int					cmd_id;
	char				**args;
	int					conex;
	int					fd_in;
	char				*file_in;
	char				*file_out;

	struct s_shell_list	*next;
	struct s_shell_list	*prev;

}						t_shell_list;

// core

int						minishell(char **env);

// strings

size_t					ft_strlen(char const *str);
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
void					clean_astr(char **astr);
char					**ft_astr_dup(char **astr);
char					**ft_astr_dup_add(char **astr, char *nw);
char					**ft_astr_extend(char **astr, char *nw);

// numeric

// long					ft_atoi(char *str);

// memory

int						my_alloc(size_t size, size_t len, void **dst);

// lists

t_shell_list			new_node(int id, char **args, int conex);
void					set_node_fds(int fd_in, int fd_out, char file_in);
void					clean_list(t_shell_list **begining);

// env

char					*get_env(char *name, char **env);
void					remove_env(char *name, char **env);
void					add_env(char *new_env, char **env);
void					change_env(char *new_env, char **env);

// execs

int						path_exec(char **args, char **env);
int						local_exec(char **args, char **env);

// built ins

int						ft_echo(char *arg, char **env);
int						ft_cd(char *arg, char **env);
int						ft_pwd(char **env);
int						ft_export(char **env);
int						ft_unset(char **env);
int						ft_exit(char **env);

// fds

void					set_fds(int fd_in, int fd_out);

// signals

// pharsing

// list execution

// exit

#endif