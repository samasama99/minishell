#ifndef MAIN_H
# define MAIN_H
# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>

// int	g_last_return;
typedef struct s_data{
	int		g_last_return;
	bool	g_forked;
	bool	g_heredoc_end;
}	t_data;

t_data	g_data;

/******* GENERAL  UTILS ********/

void		perror_exit(void);
char		*ft_strjoin_free(char *s1, char *s2);
void		panic(bool con, char *msg, const char *func);
bool		is_equal_str(const char *s1, const char *s2);

/******* 2D_ARRAY *******/

void		free_2d_array(char **array);
size_t		size_of_2d_array(char **array);
int			find_in_2d_array(char **array, char *str);

char		**init_2d_array(void);
char		**add_element_2d_array_last(char **array, char *elem);
char		**add_element_2d_array(char **array, char *elem, size_t index);

/******* SHELL UTILS ********/

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

void		ft_add_history(char *cmd);
char		*find_value(t_env *env, char *key);
char		**t_env_to_2d_array(t_env *denv);

void		free_env(t_env *env);
void		safe_close(int fd);
void		safe_close_2(int in, int out);
void		print_a_sorted_env(t_env *env, int fd);
void		add_variable_back(t_env **list, t_env *new_var);

t_env		*dup_env(char **env);
t_env		*find_key(t_env *env, char *key);
t_env		*create_variable(char *key, char *value);

/******* TOKENIZER *****/

enum e_token_types {redirection, word, pip, space, d_quote, s_quote, key};

typedef struct s_token
{
	char			*elem;
	int				type;
	struct s_token	*next;
}	t_token;

bool		is_keyword(char c);
bool		is_quote(char c);

char		*return_token_type(int type);
char		*add_keyword_token(t_token **head, char *current, bool open);

void		free_token(t_token *token);
void		free_tokens(t_token *token);
void		add_token_back(t_token **list, t_token *elem);
void		delete_first_token(t_token **list);
void		pip_token(t_token **head);
void		redirection_token(t_token **head, char *line);
void		quote_token(t_token **head, char *current, bool open);
void		space_token(t_token **head);
void		add_word_token(t_token **head, char *start, char *end);
void		add_key_token(t_token **head, char *start, char *end);
void		tokenizer(t_token **head, char *line);

t_token		*create_token(char *elem, int type);
t_token		*get_last_token(t_token *token);

/******* PARSER	*****/

typedef struct s_seq
{
	int				in;
	int				out;
	char			**args;
	struct s_seq	*next;
}	t_seq;

int			ft_fork(void);
int			ret_wait(int pid);
int			heredoc(char *delimiter);
bool		syntax_analysis(t_token *tokens);
int			free_and_exit(char *s1, char *s2, int fd1, int fd2);
void		dfl(int sig);
void		eval_io(t_seq *seq, char *rederiction_type, char *file);
void		free_seq(t_seq *seq);
void		eval_pipes(t_seq *seq);
void		add_seq_back(t_seq **list, t_seq *new_seq);

t_seq		*parser(t_token *list);
t_seq		*get_last_seq(t_seq *seq);
t_seq		*parsing(char *line, t_env *denv);
t_seq		*create_seq(char **args, int in, int out);

t_token		*corrector(t_token *token);
t_token		*expander(t_token *token, t_env *env);
t_token		*eval_redirection(t_seq *seq, t_token *token);

size_t		seq_size(t_seq *seq);

/******* EVAL ********/

enum	e_builtins {e_echo, e_env, e_export, e_unset, e_cd, e_pwd, e_exit};

int			is_builtin(char *cmd);

char		**ft_split_paths(char **env);
char		*test_paths(char *cmd, char **paths);
char		*find_in_path(char *cmd, char **env);

void		shell_loop(t_env **denv);
void		eval_seq(t_seq *list, t_env **env);
void		exec_builtin(t_env **env, t_seq *seq, int builtin);

/******* BUILTINS ********/

void		becho(char **args, int fd);
void		bcd(char *path, t_env **env);
void		bexport(char **args, t_env **env, int fd);
void		bunset(char **args, t_env **env);
void		benv(t_env *env, int fd);
void		bpwd(int fd);
void		bexit(char **args, t_seq *seq, t_env *denv, char *line);

#endif
