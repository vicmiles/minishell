/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:10:20 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 13:55:33 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_parse_error	parser_error;
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
bool	ft_star_match(char *pattern, char *str);

// * ft_clean_empty_str.c *
char	*ft_clean_empty_str(char *str);

// * ft_expand_utils.c *
bool	ft_valid_char(char c);
char	*ft_str_handle(char *str, size_t *i);
char	*ft_squote_handle(char *str, size_t *i);
char	*ft_handle_dquotes(char *str, size_t *i);

// * ft_expand.c *
char	*ft_dollar_handle(char *str, size_t *i);
char	**ft_expand(char *str);
char	*ft_get_envlst_val(char *key);

// * ft_expand_split.c *
char	**ft_expand_split(const char *str);

// * ft_file_expander_utils.c
bool	ft_contain_star(char *str);
size_t	ft_arraystr_len(char **array_str);
size_t	ft_count_match(char *pattern);
char	**ft_arraystr_join(char ***array_str);

// * ft_file_expander.c *
char	**ft_file_expander(char **expand);

// * ft_unquote.c *
char	*ft_unquote(char *str);

// * ft_expand_heredoc.c *
void	ft_expand_heredoc(char *str, int fd);

//CLEANING
void	ft_clean_ms(void);
void	ft_del(void *ptr);

// Built_in_func
int		ft_echo(char **args);
int		ft_pwd(void);
bool	ft_entry_env_exist(char	*key);
char	*ft_envlist_value(char *key);
void	ft_envlist_addback(t_env	*new);
void	ft_update_envlist(char *key, char *value, bool new);
char	*ft_extract_key(char *str);
char	*ft_extract_value(char *str);
void	ft_init_envlist(void);
int		ft_env(void);
int		ft_exec_builtin(char **args);
bool	ft_is_builtin(char *arg);
int		ft_cd(char *path);
int		ft_unset(char **args);
int		ft_exit(char **args);
int		ft_export(char **args);
void	print_env_vars(void);

// Executor
int		ft_exec_node(t_node *tree, bool piped);
int		ft_get_exit_status(int status);

// Exec.utils
void	*ft_garbage_collector(void *ptr, bool clean);

//Exec_simple_cmd
int		ft_exec_simple_cmd(t_node *node, bool piped);

// init_tree
void	ft_heredoc(t_io_node *io, int p[2]);
void	ft_init_tree(t_node *node);
bool	ft_is_delimiter(char *delimiter, char *str);

/* MINISHELL */
// * main_signals.c *
void	ft_sigquit_handle(int num);
void	ft_signals(void);
int		ft_err_msg(t_err err);
t_err	ft_check_exec(char *file, bool cmd);
t_err	ft_check_read(char *file);
t_err	ft_check_write(char *file);
t_path	ft_get_path(char *cmd);
void	ft_reset_stds(bool piped);
int		ft_check_redirection(t_node *node);
int		ft_append(t_io_node *io_list, int *status);
int		ft_in(t_io_node *io_list, int *status);
int		ft_out(t_io_node *io_list, int *status);

#endif
