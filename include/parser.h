/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:25:03 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 12:52:46 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define PROMT "minishell$"

typedef enum e_node_type
{
	N_PIPE,
	N_OR,
	N_AND,
	N_CMD
}	t_node_type;

typedef enum e_io_type
{
	IO_IN,
	IO_OUT,
	IO_HEREDOC,
	IO_APPEND
}	t_io_type;

typedef enum e_parse_error_type
{
	E_MEM = 1,
	E_SYNTAX
}	t_parse_error_type;

typedef struct s_io_node
{
	t_io_type			type;
	char				*value;
	char				**expand_value;
	int					here_doc;
	struct s_io_node	*next;
	struct s_io_node	*prev;
}	t_io_node;

typedef struct s_node
{
	t_node_type		type;
	t_io_node		*io_list;
	char			*args;
	char			**expand_args;
	char			**cmd;
	struct s_node	*right;
	struct s_node	*left;
}	t_node;

typedef struct s_parse_error
{
	t_parse_error_type	type;
	char				*str;
}	t_parse_error;

// *parser_clean.c
void		ft_clear_iolist(t_io_node **list);
void		ft_clear_cmdnode(t_node *node);
void		ft_recursive_clear(t_node *node);
void		ft_clear_ast(t_node **ast);

// *parser_error.c
void		ft_parse_error(t_parse_error_type type);
void		ft_manage_parser_error(void);

// *parser_node_utils.c
bool		ft_get_iolist(t_io_node **io_list);
bool		ft_join_args(char **args);
t_node		*ft_get_simple_cmd(void);

// *parser_node.c
t_node_type	ft_node_type(t_token_type token);
t_io_type	ft_io_type(t_token_type type);
t_node		*ft_new_node(t_node_type type);
t_io_node	*ft_new_ionode(t_token_type type, char *value);
void		ft_append_ionode(t_io_node **list, t_io_node *new);

// *parser_utils.c
void		ft_get_next_token(void);
bool		ft_curr_token_binop(void);
bool		ft_isredir(t_token_type token);
int			ft_prior(t_token_type token);
int			ft_curtoken_prior(void);

// *parser.c
t_node		*ft_term(void);
t_node		*ft_combine(t_token_type op, t_node *left, t_node *right);
t_node		*ft_expression(int min_prior);
t_node		*ft_parse(void);

#endif
