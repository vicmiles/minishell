/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:00:47 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 12:22:39 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_iolist(t_io_node **list)
{
	t_io_node	*current_node;
	t_io_node	*next;

	current_node = *list;
	if (!current_node)
		return ;
	while (current_node)
	{
		free(current_node->value);
		ft_free_char2(current_node->expand_value);
		next = current_node->next;
		free(current_node);
		current_node = next;
	}
	*list = NULL;
}

void	ft_clear_cmdnode(t_node *node)
{
	if (!node)
		return ;
	ft_clear_iolist(&(node -> io_list));
	free(node -> args);
	ft_free_char2(node->expand_args);
}

void	ft_recursive_clear(t_node *node)
{
	if (!node)
		return ;
	if (node -> type == N_CMD)
		ft_clear_cmdnode(node);
	else
	{
		if (node -> left)
			ft_recursive_clear(node->left);
		if (node -> right)
			ft_recursive_clear(node -> right);
	}
	free(node);
}

void	ft_clear_ast(t_node **ast)
{
	ft_recursive_clear(*ast);
	*ast = NULL;
	ft_clear_token_list(&g_minishell.tokens);
}
