/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:27:58 by vkhut             #+#    #+#             */
/*   Updated: 2025/05/07 12:28:38 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_entry_env_exist(char	*key)
{
	t_env	*envlist;

	envlist = g_minishell.envlst;
	while (envlist)
	{
		if (!ft_strcmp(key, envlist->key))
			return (true);
		envlist = envlist->next;
	}
	return (false);
}

static t_env	*ft_new_envlist(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_garbage_collector(ft_strdup(key), false);
	if (value)
		new->value = ft_garbage_collector(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}

char	*ft_envlist_value(char *key)
{
	t_env	*envlist;

	envlist = g_minishell.envlst;
	while (envlist)
	{
		if (!ft_strcmp(key, envlist->key))
			return (envlist->value);
		envlist = envlist->next;
	}
	return (NULL);
}

void	ft_envlist_addback(t_env	*new)
{
	t_env	*curr;

	if (!g_minishell.envlst)
	{
		g_minishell.envlst = new;
		return ;
	}
	curr = g_minishell.envlst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}

void	ft_update_envlist(char *key, char *value, bool new)
{
	t_env	*envlist;

	envlist = g_minishell.envlst;
	while (envlist)
	{
		if (!ft_strcmp(key, envlist->key))
		{
			if (value)
				envlist->value = ft_garbage_collector(ft_strdup(value), false);
			return ;
		}
		envlist = envlist->next;
	}
	if (new)
		ft_envlist_addback(ft_new_envlist(key, value));
}
