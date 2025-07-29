/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:21:30 by vkhut             #+#    #+#             */
/*   Updated: 2025/05/07 12:23:14 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_newline(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (false);
	i = 0;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(char **args)
{
	int		i;
	bool	no_newline;

	i = 1;
	no_newline = (false);
	while (args[1] && is_newline(args[i]))
	{
		no_newline = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!no_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
