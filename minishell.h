/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:03:50 by momayaz           #+#    #+#             */
/*   Updated: 2022/07/16 17:52:19 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* **************************** LIBRARIES **************************** */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <dirent.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>

/* **************************** DEFINES **************************** */
# define TABLE "|&<>"
# define WHITESPACE " \n\r\v\t\f"
# define PIPE 0
# define OR 1
# define AND 2
# define COMMAND 3

/* **************************** STRUCTS **************************** */
typedef struct s_garbage
{
	void				**addr;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_tree
{
	char			token;
	int				is_builtin;
	char			**cmd;
	char			**env;
	char			*path;
	char			*infile;
	char			*outfile;
	int				ifd;
	int				ofd;
	int				p[2];
	int				exist;
	struct s_tree	*parent;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

typedef struct s_wild
{
	char			**t;
	int				i;
	int				len;
	DIR				*dir;
	struct dirent	*wild;
}	t_wild;

typedef struct s_all
{
	t_garbage	*g_head;
	t_env		*env_head;
	t_tree		*root;
	char		**env;
	int			status;
	int			status_s;
	int			pid;
	int			j;
	int			k;
	int			lr;
	int			i;
	int			a;
	int			exi;
	int			exk;
	int			exj;
	int			count;
}	t_all;

t_all	g_all;
/* **************************** UTILS **************************** */
size_t		ft_strlen(char *s);
int			ft_isalpha(int c);
int			ft_isalnum(int c);
int			ft_skip_quote(char *str, int *i);
void		ft_skip_par(char *str, int *i);
void		ft_skip_par_rev(char *str, int *i);
int			ft_skip_quote_rev(char *str, int *i);
void		ft_print_error(char *s1, char *s2, char *s3);
void		free_tab(char **t);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strdup(char *s1);
int			ft_strchr(char *s, int c);
int			ft_strrchr(char *s, int c);
int			ft_strchr_v2_0(char *str);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
char		*ft_substr(char *s, unsigned int start, size_t len);
void		ft_sub_len(char *s, unsigned int start, size_t *len);
char		*ft_substr2(char *s, unsigned int start, size_t len);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin2(char *s1, char *s2);
char		**ft_split(char *s, char c);
t_tree		*ft_new_node(int token, char **cmd);

/* **************************** ENV FUNCTIONS **************************** */
t_env		*ft_new_env(char *key, char *value);
void		ft_add_env(t_env **lst, t_env *new);
int			ft_env_split(const char *s);
void		ft_free_env(void);
void		ft_edit_env(t_env *env, char *key, char *new_val);
char		*ft_get_env(t_env *head, char *search);
void		ft_env_init(t_env **env, char *s_env[]);
char		**ft_list_to_array(void);

/* **************************** CHECK SYNTAX **************************** */
int			ft_check_options(char *str);
int			ft_valid_options_mini(char c, char get, int *cp);
int			ft_valid_options(char *str);
int			ft_valid_parenthesis_mini(char *str, int *i, int *cp);
int			ft_valid_parenthesis_norm(char *str, int *i, int *cp);
int			ft_valid_parenthesis(char *str);
int			ft_check_syntax(char *str);

/* *************************** GARBAGE FUNCTIONS *************************** */
t_garbage	*ft_new_garbage(void **addr);
void		ft_add_garbage(t_garbage **lst, t_garbage *new);
void		ft_free_garbage(t_garbage *garbage);
void		**ft_malloc(int alloc);
char		*ft_strtrim(char *s1, char *set);
char		*ft_substr_garbage(char *s, unsigned int start, size_t len);
char		*ft_strdup_garbage(char *s1);

/* *************************** FILES FUNCTIONS *************************** */
void		ft_heredoc(char *limiter, int fd);
char		*ft_get_herdoc(char *str, int i, t_tree **node);
char		*ft_get_infile(char *str, int i, t_tree **node);
void		ft_split_red_mini(t_tree **node, char **str, int *i);
void		ft_split_red(char **str, t_tree **node);
char		*ft_get_outfile(char *str, int i, t_tree **node);
char		*ft_get_a_outfile(char *str, int i, t_tree **node);

/* *************************** BUILTIN FUNCTIONS *************************** */
int			ft_env(t_env *lst);
int			ft_pwd(void);
int			ft_echo(int index, char **s);
int			ft_cd(t_env *env, char *s);
int			ft_export(char **str, t_env *head, int cp);
void		ft_affiche_export(t_env *head);
int			ft_export_mini_mini(char **str, t_env *head);
int			ft_unset(t_env **lst, char *str);
void		ft_exit(char **cmd);

/* *************************** PARSING FUNCTIONS *************************** */
void		ft_tree_init(char *str);
char		*ft_parse_dollar(char *str, int n);
char		**ft_split_echo(char *str);
char		**ft_double_join(char **s1, char **s2, int pos);
char		**etoile(t_wild wi);
int			ft_get_path(t_tree *node, char **path);
void		ft_fill_tree(t_tree **node, char *str, t_tree *parent);

/* ************************** EXECUTION FUNCTIONS ************************** */
void		exitstatuses(void);
void		execmini(t_tree *root);
void		execbultincmd(t_tree *root);
void		execnbultinone(t_tree *root);
void		execnbultin(t_tree *root);
void		executerpipe(t_tree *root, int p[2], int i);
void		execpipe(t_tree *root);
void		checkdollar(char **str);
void		execmini(t_tree *root);
void		handc(int sig);
void		handlerback(int sig);
#endif
