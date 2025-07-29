/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:35:35 by vkhut             #+#    #+#             */
/*   Updated: 2025/05/07 12:36:50 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args)
{
	t_env	*temp;
	t_env	*prev;

	temp = g_minishell.envlst;
	prev = NULL;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, args[1]) == 0)
		{
			if (prev == NULL)
			{
				g_minishell.envlst = temp->next;
			}
			else
			{
				prev->next = temp->next;
			}
			free(temp);
			break ;
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}
