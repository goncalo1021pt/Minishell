#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

typedef struct s_shell_tree{

int     cmd_id;
char    **args;
int		conex;
int     fd_in;
char    *file_in;
char    *file_out;


struct s_shell_tree *left;
struct s_shell_tree *right;
    
} t_shell_tree;


// core

int minishell(char **env);


// strings

size_t	ft_strlen(char const *str);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_f1(char *s1, char const *s2);
char	*ft_strjoin_f2(char const *s1, char *s2);
char	*ft_strjoin_f12(char *s1, char *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *str);
void	clean_astr(char **astr);
char    **ft_astr_dup(char **astr);
char	**ft_astr_dup_add(char **astr, char *nw);
char	**ft_astr_extend(char **astr, char *nw);

// numeric 

long	ft_atoi(char *str);

// memory

int	my_alloc(size_t size, size_t len, void **dst);

// trees

t_shell_tree    new_node(int id, char **args, int conex);
void    set_node_fds(int fd_in, int fd_out, char file_in, char file_out);
void    clean_tree(t_shell_tree **begining);

// env

char    *get_env(char *name, char **env);
void	remove_env(char *name, char **env);
void	add_env(char *new_env, char **env);
void	change_env(char *new_env, char **env);

// execs

int path_exec(char **args, char **env);
int local_exec(char **args, char **env);

// built ins

int ft_echo(char *arg, char **env);
int ft_cd(char *arg, char **env);
int ft_pwd(char **env);
int ft_export(char **env);
int ft_unset(char **env);
int ft_exit(char **env);

// fds

void	set_fds(t_shell_tree_node *node);

// signals

// pharsing

// tree execution

//exit

#endif