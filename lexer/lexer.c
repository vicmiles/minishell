/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:21:17 by vmileshk          #+#    #+#             */
/*   Updated: 2025/04/23 15:00:34 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lexer(void)
{
	char	*line;
	t_token	*token_list;

	line = g_minishell.line;
	token_list = ft_lexer_handler(line);
	free(line);
	g_minishell.line = NULL;
	return (token_list);
}
