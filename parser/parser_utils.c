/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:15:32 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 12:19:04 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_next_token(void)
{
	g_minishell.curr_token = g_minishell.curr_token -> next;
}

bool	ft_curr_token_binop(void)
{
	t_token_type	type;

	if (!g_minishell.curr_token)
		return (false);
	type = g_minishell.curr_token->type;
	if (type == T_PIPE || type == T_AND || type == T_OR)
		return (true);
	return (false);
}

bool	ft_isredir(t_token_type type)
{
	if (type == T_LESS || type == T_GREAT \
		|| type == T_DLESS || type == T_DGREAT)
		return (true);
	return (false);
}

int	ft_prior(t_token_type type)
{
	if (type == T_OR || type == T_AND)
		return (0);
	return (1);
}

int	ft_curtoken_prior(void)
{
	return (ft_prior(g_minishell.curr_token->type));
}
