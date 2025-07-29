/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:07:42 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 12:21:16 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_get_iolist(t_io_node **io_list)
{
	t_token_type	redir_type;
	t_io_node		*tmp_io_node;

	if (g_minishell.parser_error.type)
		return (false);
	while (g_minishell.curr_token && ft_isredir(g_minishell.curr_token->type))
	{
		redir_type = g_minishell.curr_token->type;
		ft_get_next_token();
		if (!g_minishell.curr_token)
			return (ft_parse_error(E_SYNTAX), false);
		if (g_minishell.curr_token->type != T_IDENTIFIER)
			return (ft_parse_error(E_SYNTAX), false);
		tmp_io_node = ft_new_ionode(redir_type, g_minishell.curr_token->value);
		if (!tmp_io_node)
			return (ft_parse_error(E_MEM), false);
		ft_append_ionode(io_list, tmp_io_node);
		ft_get_next_token();
	}
	return (true);
}

bool	ft_join_args(char **args)
{
	char	*line;

	if (g_minishell.parser_error.type)
		return (false);
	if (!*args)
		*args = ft_strdup("");
	if (!*args)
		return (false);
	while (g_minishell.curr_token \
		&& g_minishell.curr_token->type == T_IDENTIFIER)
	{
		line = *args;
		*args = ft_strjoin_with(*args, g_minishell.curr_token -> value, ' ');
		if (!*args)
			return (free(line), false);
		free(line);
		ft_get_next_token();
	}
	return (true);
}

t_node	*ft_get_simple_cmd(void)
{
	t_node	*node;

	if (g_minishell.parser_error.type)
		return (NULL);
	node = ft_new_node(N_CMD);
	if (!node)
		return (ft_parse_error(E_MEM), NULL);
	while (g_minishell.curr_token \
		&& (g_minishell.curr_token->type == T_IDENTIFIER \
			|| ft_isredir(g_minishell.curr_token->type)))
	{
		if (g_minishell.curr_token->type == T_IDENTIFIER)
		{
			if (!ft_join_args(&(node -> args)))
				return (ft_clear_cmdnode(node), ft_parse_error(E_MEM), NULL);
		}
		else if (ft_isredir(g_minishell.curr_token->type))
		{
			if (!ft_get_iolist(&(node->io_list)))
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}
