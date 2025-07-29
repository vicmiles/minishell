/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:39:08 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 13:48:49 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_expand_braced_var(char *str, size_t i, int fd)
{
	char	*tmp;
	size_t	b;

	b = ++i;
	while (str[i] && str[i] != '}')
		i++;
	if (str[i] == '}')
	{
		tmp = ft_envlist_value(ft_garbage_collector(\
			ft_substr(str, b, i - b), false));
		if (tmp)
			ft_putstr_fd(tmp, fd);
		return (i + 1);
	}
	return (b - 2);
}

static int	ft_writer_heredoc(char *str, size_t i, int fd)
{
	char	*tmp;
	size_t	start;

	start = ++i;
	if (str[i] == '?')
	{
		ft_putnbr_fd(g_minishell.exit_s, fd);
		return (2);
	}
	if (str[i] == '{')
		return (ft_expand_braced_var(str, i, fd));
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	if (i != start)
	{
		tmp = ft_envlist_value(ft_garbage_collector(\
			ft_substr(str, start, i - start), false));
		if (tmp)
			ft_putstr_fd(tmp, fd);
		else
			ft_putstr_fd("", fd);
	}
	else
		ft_putchar_fd('$', fd);
	return (i);
}

void	ft_expand_heredoc(char *str, int fd)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += ft_writer_heredoc(str, i, fd);
		else
			i += (ft_putchar_fd(str[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}
