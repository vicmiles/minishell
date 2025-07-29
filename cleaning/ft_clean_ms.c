/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:08:47 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 13:55:12 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_envlst(void)
{
	t_env	*envlst;
	t_env	*envlst_free;

	envlst = g_minishell.envlst;
	while (envlst)
	{
		envlst_free = envlst;
		envlst = envlst->next;
		free(envlst_free);
	}
	g_minishell.envlst = NULL;
}

void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	ft_clean_ms(void)
{
	ft_garbage_collector(NULL, true);
	ft_clear_ast(&g_minishell.ast);
	ft_clear_envlst();
	rl_clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);
}
