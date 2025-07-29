/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_star.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:43:19 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 13:25:41 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_quotes(char **pattern, char *quotes)
{
	if (**pattern == '"' || **pattern == '\'')
	{
		if (!*quotes)
			*quotes = *(*pattern)++;
		else
		{
			if (*quotes == **pattern)
			{
				*quotes = 0;
				(*pattern)++;
			}
		}
	}
}

static bool	ft_more_stars(char **pattern, char **last_wildcard, \
	char **last, char *str)
{
	while (**pattern == '*')
		(*pattern)++;
	if (!**pattern)
		return (true);
	*last_wildcard = *pattern;
	*last = str;
	return (false);
}

static bool	ft_match_pattern(char **pattern, char **last_wildcard, \
	char **last, char **str)
{
	if (**pattern == **str)
	{
		(*pattern)++;
		(*str)++;
		return (true);
	}
	else if (*last_wildcard)
	{
		*str = ++(*last);
		*pattern = *last_wildcard;
		return (true);
	}
	else
		return (false);
}

bool	ft_star_match(char *pattern, char *str)
{
	char	*last_wildcard;
	char	*last;
	char	quotes;

	quotes = 0;
	last_wildcard = NULL;
	last = NULL;
	while (*str)
	{
		ft_quotes(&pattern, &quotes);
		if (*pattern == '*' && !quotes \
			&& ft_more_stars(&pattern, &last_wildcard, &last, str))
			return (true);
		else if (!ft_match_pattern(&pattern, &last_wildcard, &last, &str))
			return (false);
	}
	if (*pattern == '*')
		while (*pattern == '*')
			pattern++;
	return (!*pattern);
}
