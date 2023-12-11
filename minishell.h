/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:25:22 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 04:49:29 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <libc.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/_types/_null.h>
# include <sys/ioctl.h>
# include <sys/signal.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/_types/_null.h>
# include <sys/fcntl.h>
# include <sys/unistd.h>
# include <sys/wait.h>
# include <unistd.h>

int						g_end;

typedef struct s_collector
{
	void				*ptr;
	struct s_collector	*next;
}						t_collector;

typedef struct s_heredoc
{
	char		*env_val;
	char		*result;
	char		*s;
	int			env_n_l;
	int			i;
}						t_heredoc;

typedef struct env
{
	char				*name;
	char				*val;
	char				*line;
	struct env			*next;
}						t_env;

typedef struct s_stracto
{
	int					**pips;
	int					i;
	int					n;
	int					a;
	t_env				**expando;
}						t_stracto;

enum					e_tokenizing
{
	WORD = -1,
	IN_QUOTE,
	IN_DQUOTE,
	QUOTE = '\'',
	D_QUOTE = '\"',
	ENV = '$',
	_PIPE = '|',
	HERE_DOC,
	RDR_IN = '<',
	APPEND,
	RDR_OUT = '>',
	_NULL = '0',
};

typedef struct s_anelement
{
	char				*content;
	int					is_ex;
	enum e_tokenizing	tk;
	int					len;
	struct s_anelement	*prev;
	struct s_anelement	*next;
}						t_anelement;

typedef struct s_cmd
{
	char				**args;
	int					is_red_or_app;
	int					in_out;
	int					expand_heredoc;
	int					fd_in;
	int					h_i;
	int					fd_heredoc;
	char				**infl;
	char				**outfl;
	char				**heredoc_del;
	int					pid;
	char				*path;
	struct s_cmd		*next;
}						t_cmd;

// tokenize function :

/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/
enum e_tokenizing		type(t_anelement **elem, char *l, int i);

int						rdr_out_push(char *l, t_anelement **elem, int i,
							t_anelement **h);
int						rdr_in_push(char *l, t_anelement **elem, int i,
							t_anelement **h);
int						word_push(char *l, t_anelement **elem, int i,
							t_anelement **h);
int						q_dq_push(char *l, t_anelement **elem, int i,
							t_anelement **h);
int						pipe_push(char *l, t_anelement **elem, int i,
							t_anelement **h);

void					element(t_anelement **elem, char *l, int i,
							t_anelement **h);
void					ft_anelemtadd_back(t_anelement **head,
							t_anelement *new);
void					tokenize(t_anelement **head, char **splited);
/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/

// utils:

/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/
void					zeero(int *i, int *t, int *start, int *inquotes);
void					quote_state(char c, int *inquotes);
void					*ft_malloc(size_t size);

int						numberofpipes(t_anelement *head_a);
int						ft_striswspace(char *str);
int						wordc(char const *s);
int						ft_is_special(char c);
int						ft_readline(char **l);
int						ft_iswspace(char c);

char					*ft_strncpy(char *s1, char *s2, int n);
char					**ft_split2(char *s);
/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/

// expand&quotes:

/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/

char					*expand_heredoc(char *line, t_env **all);

void					quotes_handel_and_expand(t_anelement *head,
							t_env **all);
void					cn(int inside, int *q);
char					*join_one(char *str, char c);
char					*quotes_inside_general_expnad(t_anelement *elem,
							char **env);
char					*handler(t_anelement *head, t_env **all);
char					*expand(t_anelement *elem, char **env);

int						check_valid_env(char *s, t_anelement *elem);
int						how_much_expand(t_anelement *elem);
int						checking_quotes(char *l);
int						get_key_len(char *key);

/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/

// others:

/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/
void					ft_lstadd_back_clctr(t_collector **lst,
							t_collector *new);

void					start_minish(t_env **all, t_cmd **data);

void					syntax_errors_return_status(int x);
void					ft_freeee(t_anelement **elem);
void					ft_freee(t_cmd **data);
void					set_exit_status(int i);
void					ft_ext(int i);

int						ft_exit_status(int i, int status);
int						syntax_error(t_anelement *head);
int						get_exit_status(void);

t_collector				*ft_lstnew_clctr(void *l3iba);
t_collector				**ft_garbege_collector(void);

/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/

// cmd :

/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/
void					finish_them(t_cmd *data, t_anelement *apin, int j);
void					args(t_cmd *lexing, t_anelement *elem, int j);
void					ft_cmd_back(t_cmd **head, t_cmd *new);

int						here_doc(t_cmd *data, t_anelement *elem);
int						in_file(t_cmd *data, t_anelement *elem);
int						number_of_args(t_anelement *head);
int						diff_to(t_anelement *elem);

t_anelement				*outf_app(t_cmd *data, t_anelement *elem);

t_cmd					*parser(char *l, t_env **env);

/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/

// execution :

/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/
void					make_node(t_env **all, char *val, char *name,
							char *line);

void					fill_list(t_env **all, char **env);
void					ft_unset(t_env **all, t_cmd *com);
void					ft_cd(t_env **all, t_cmd *com);
void					ft_write(int fd, char *str);
void					print_env(t_env **all);
void					print_list(t_env *tmp);
void					sig_handler(int sig);
void					ft_echo(t_cmd *com);
void					ft_exit(t_cmd *com);
void					handle_exe(int sig);
void					ft_pwd(t_env **all);

char					*find_name(t_env **all, char *key, int keylen);
char					*ft_strjoin(char const *s1, char const *s2);
char					**ft_split(char const *s, char c);
char					*full_line(char *env);
char					*name_fun(char *env);
char					*val_fun(char *env);
char					*ft_strchr(const char *str, int c);

int						ft_strcmp(const char *s1, const char *s2);
int						ft_exe(t_env **all, t_cmd *com);
int						ft_export(t_env **all, t_cmd *com);
int						ft_env(t_env **all, t_cmd *com);
int						valid_name(char *str);
int						name_len(char *env);
int						val_len(char *env);
int						beg(char c);
void					ft_write3(char *s1, char *s2);
int						ft_built(t_env **all, t_cmd *com);
char					*exe_com(t_env **all, t_cmd *com);
t_env					*ft_search(t_env **all, char *name);
int						num_d(char **here);
int						pip_num(t_cmd *com);
int						funco(char *line, t_cmd *com, int fd[2],
							t_stracto stracto);
int						ft_heredoc(t_cmd *com, t_env **all);
void					ft_write3(char *s1, char *s2);
int						outfile(t_cmd *com);
int						infile(t_cmd *com);
void					in_pipe(int **pips, int i);
int						in_com(t_cmd *com, int **pips, int i);
int						out_com(t_cmd *com, int **pips, int n, int i);
int						**alloc_pipes(int n);
void					close_all(int **pips, int n);
char					**env_to_char(t_env *env);
void					exc2(char *path, t_cmd *com, char **env);
void					dir_k(DIR *k);
void					ft_exech(t_env **all, t_cmd *com, char **env,
							t_stracto stract);
int						is_built(char *command);
void					here_beg(t_cmd *com, t_env **all);
int						wait_all(int **pips, t_cmd *tmp, t_cmd *tmp3, int n);
void					sort_list(t_env **exp);
void					ft_swap(t_env *cur, t_env *next);
void					ft_write(int fd, char *str);
void					copy_list(t_env **all, t_env **tmp);
void					free_list(t_env *tmp);
void					add_helper(t_env *tmp, char *str, char *val, int v);
void					nothing(int sig);
/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/

// libft function :

/*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/ /*/*/
/*/*/ /*/*/																/*/*/

char					*ft_substr(char const *s, unsigned int start,
							size_t len);
void					zero(size_t *i, size_t *t, int *start, int *inquotes);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strjoin(char const *s1, char const *s2);
void					*ft_calloc(size_t count, size_t size);
char					**ft_split(char const *s, char c);
char					**freedown(char **str, int i);
void					ft_bzero(void *s, size_t n);
size_t					ft_strlen(const char *str);
char					*ft_strdup(const char *s1);
int						ft_atoi(const char *str);
int						ft_isdigit(int c);
int						ft_isalpha(int c);
int						ft_isalnum(int c);
char					*ft_itoa(int n);
int						nlen(long n);

#endif