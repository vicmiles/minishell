#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_err_msg
{
	ERRMSG_CMD_NOT_FOUND,
	ERRMSG_NO_SUCH_FILE,
	ERRMSG_PERM_DENIED,
	ERRMSG_AMBIGUOUS,
	ERRMSG_TOO_MANY_ARGS,
	ERRMSG_NUMERIC_REQUI
}	t_err_msg;

typedef enum e_err_no
{
	ENO_SUCCESS,
	ENO_GENERAL,
	ENO_CANT_EXEC = 126,
	ENO_NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_err_no;

typedef enum e_ast_direction
{
	TD_LEFT,
	TD_RIGHT
}	t_ast_direction;

typedef struct s_err
{
	t_err_no	no;
	t_err_msg	msg;
	char		*cause;
}	t_err;

typedef struct s_path
{
	t_err	err;
	char	*path;
}	t_path;

typedef struct s_minishell
{
	char			*line;
	t_token			*tokens;
	t_token			*curr_token;
	t_node			*ast;
	int				exit_s;
	bool			signint_child;
	t_parse_err		parse_err;
	int				stdin;
	int				stdout;
	char			**environ;
	t_env			*envlst;
	bool			heredoc_sigint;
	struct termios	original_term;
}					t_minishell;

extern t_minishell	g_minishell;

/* EXPANDER */
// * ft_star.c
bool    ft_star_match(char **pattern, char *str);

// * ft_clean_empty_str.c *
char    *ft_clean_empty_str(char *str);

// * ft_expand_utils.c *
bool	ft_valid_char(char c);
char	*ft_str_handle(char *str, size_t *i);
static char	*ft_subdquote_handle(char *str, size_t *i);
char	*ft_squote_handle(char *str, size_t *i);
char	*ft_handle_dquotes(char *str, size_t *i);

// * ft_expand.c *
char	*ft_dollar_handle(char *str, size_t *i);
char	**ft_expand(char *str);

// * ft_expand_split.c *
char    **ft_expand_split(const char *str);

// * ft_file_expander_utils.c
bool    ft_contain_star(char *str);
size_t  ft_arraystr_len(char **array_str);
size_t  ft_count_match(char *pattern);
char **ft_arraystr_join(char **array_str);

// * ft_file_expander.c *
char *ft_file_expander(char **expand);

// * ft_unquote.c *
char    *ft_unquote(char *str)

// * ft_expand_heredoc.c *
void    ft_expand_heredoc(char *str, int fd);

/* MINISHELL */
// * main_signals.c *
void	ft_sigquit_handle(int num);
void	ft_signals(void);

#endif