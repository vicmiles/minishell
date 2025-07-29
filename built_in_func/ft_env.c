/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:26:03 by vkhut             #+#    #+#             */
/*   Updated: 2025/05/07 12:27:25 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_garbage_collector(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}

char	*ft_extract_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_garbage_collector(\
				ft_substr(str, i, ft_strlen(str) - i), false));
		}
		i++;
	}
	return (NULL);
}

void	ft_init_envlist(void)
{
	int		i;
	char	**environ;
	char	*key;
	char	*value;

	environ = g_minishell.environ;
	if (!environ)
		return ;
	i = 0;
	while (environ[i])
	{
		key = ft_extract_key(environ[i]);
		value = ft_extract_value(environ[i]);
		ft_update_envlist(key, value, true);
		i++;
	}
}

int	ft_env(void)
{
	t_env	*list;

	list = g_minishell.envlst;
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (ENO_SUCCESS);
}
