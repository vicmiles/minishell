/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:19:15 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 13:23:06 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define PROMT "minishell$"

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_OR,
	T_AND,
	T_NL
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// * lexer_appender.c
int		ft_append_separator(t_token_type type, char **line_ptr, \
		t_token **token_list);
int		ft_append_identifier(char **line_ptr, t_token **token_list);

// * lexer_handlers.c
int		ft_handle_separator(char **line_ptr, t_token **token_list);
t_token	*ft_lexer_handler(char *line);

// * lexer_list,c
t_token	*ft_new_token(char *value, t_token_type type);
void	ft_token_list_add_back(t_token **list, t_token *new_token);
void	ft_clear_token_list(t_token **list);

// * lexer_utils.c
int		ft_is_quote(char c);
int		ft_is_separator(char *s);
void	ft_skip_spaces(char **line);
bool	ft_skip_quotes(char *line, size_t *i);
void	ft_print_quote_err(char c);

// * lexer.c *
t_token	*ft_lexer(void);

#endif
