/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:21:06 by vmileshk          #+#    #+#             */
/*   Updated: 2025/04/22 15:24:05 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

void	ft_token_list_add_back(t_token **list, t_token *new_token)
{
	t_token	*current_node;

	if (!*list)
	{
		*list = new_token;
		return ;
	}
	current_node = *list;
	while (current_node && current_node -> next)
		current_node = current_node -> next;
	current_node -> next = new_token;
	new_token -> prev = current_node;
}

void	ft_clear_token_list(t_token **list)
{
	t_token	*current_node;
	t_token	*next;

	current_node = *list;
	if (!current_node)
		return ;
	while (current_node)
	{
		free(current_node->value);
		next = current_node->next;
		free(current_node);
		current_node = next;
	}
	*list = NULL;
}
