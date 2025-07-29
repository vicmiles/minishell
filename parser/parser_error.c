/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:01 by vmileshk          #+#    #+#             */
/*   Updated: 2025/04/23 15:07:20 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_error(t_parse_error_type type)
{
	g_minishell.parser_error.type = type;
}

void	ft_manage_parser_error(void)
{
	t_parse_error_type	type;
	t_token_type		token_type;
	char				**types;

	types = (char *[]){"T_IDENTIFIER",
		"<", ">", "<<", ">>", "|", "(", ")", "&&", "||", "newline"};
	type = g_minishell.parser_error.type;
	(void)token_type;
	(void)types;
	if (type)
	{
		if (type == E_SYNTAX)
		{
			if (!g_minishell.curr_token)
				token_type = T_NL;
			else
				token_type = g_minishell.curr_token->type;
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(types[token_type], 2);
			ft_putstr_fd("'\n", 2);
			g_minishell.exit_s = 258;
		}
		ft_clear_ast(&g_minishell.ast);
		ft_bzero(&g_minishell.parser_error, sizeof(t_parse_error));
	}
}
