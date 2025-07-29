/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:29:22 by vkhut             #+#    #+#             */
/*   Updated: 2025/05/07 12:34:32 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_err_msg(char	*ident)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(ident, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static void	ft_export_list(void)
{
	t_env	*list;
	size_t	i;

	list = g_minishell.envlst;
	while (list)
	{
		if (list->value != NULL && (ft_strcmp(list->key, "_") != 0))
		{
			printf("declare -x %s=\"", list->key);
			i = 0;
			while ((list->value)[i])
			{
				if ((list->value)[i] == '$' || (list->value)[i] == '"')
					printf("\\%c", (list->value)[i++]);
				else
					printf("%c", (list->value)[i++]);
			}
			printf("\"\n");
		}
		else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

int	ft_check_key(char	*str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(char **argv)
{
	char	*key;
	int		i;
	int		exit_code;

	exit_code = 0;
	i = 1;
	if (!argv[1])
		return (ft_export_list(), 0);
	while (argv[i])
	{
		if (ft_check_key(argv[i]) == 0)
			exit_code = ft_export_err_msg(argv[i]);
		else
		{
			key = ft_extract_key(argv[i]);
			if (ft_entry_env_exist(key))
				ft_update_envlist(key, ft_extract_value(argv[i]), false);
			else
				ft_update_envlist(key, ft_extract_value(argv[i]), true);
		}
		i++;
	}
	return (exit_code);
}
