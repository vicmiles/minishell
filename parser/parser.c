/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:17:10 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 12:23:01 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_term(void)
{
	t_node	*node;

	if (g_minishell.parser_error.type)
		return (NULL);
	if (ft_curr_token_binop() || g_minishell.curr_token->type == T_C_PARENT)
		return (ft_parse_error(E_SYNTAX), NULL);
	else if (g_minishell.curr_token->type == T_O_PARENT)
	{
		ft_get_next_token();
		node = ft_expression(0);
		if (!node)
			return (ft_parse_error(E_MEM), NULL);
		if (!g_minishell.curr_token \
			|| g_minishell.curr_token -> type != T_C_PARENT)
			return (ft_parse_error(E_SYNTAX), node);
		ft_get_next_token();
		return (node);
	}
	else
		return (ft_get_simple_cmd());
}

t_node	*ft_combine(t_token_type op, t_node *left, t_node *right)
{
	t_node	*node;

	if (g_minishell.parser_error.type)
		return (NULL);
	node = ft_new_node(ft_node_type(op));
	if (!node)
		return (ft_parse_error(E_MEM), NULL);
	node -> left = left;
	node -> right = right;
	return (node);
}

t_node	*ft_expression(int min_prior)
{
	t_node			*left;
	t_node			*right;
	int				next_prior;
	t_token_type	current_op;

	if (g_minishell.parser_error.type || !g_minishell.curr_token)
		return (NULL);
	left = ft_term();
	if (!left)
		return (NULL);
	while (ft_curr_token_binop() && ft_curtoken_prior() >= min_prior)
	{
		current_op = g_minishell.curr_token->type;
		ft_get_next_token();
		if (!g_minishell.curr_token)
			return (ft_parse_error(E_SYNTAX), left);
		next_prior = ft_prior(current_op) + 1;
		right = ft_expression(next_prior);
		if (!right)
			return (left);
		left = ft_combine(current_op, left, right);
		if (!left)
			return (ft_clear_ast(&left), ft_clear_ast(&right), NULL);
	}
	return (left);
}

t_node	*ft_parse(void)
{
	t_node	*ast;

	g_minishell.curr_token = g_minishell.tokens;
	ast = ft_expression(0);
	if (g_minishell.curr_token)
		return (ft_parse_error(E_SYNTAX), ast);
	return (ast);
}
