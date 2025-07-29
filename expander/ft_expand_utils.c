/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:33:35 by vmileshk          #+#    #+#             */
/*   Updated: 2025/04/23 15:34:06 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_valid_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	return (false);
}

char	*ft_str_handle(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

static char	*ft_subdquote_handle(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
	{
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

char	*ft_squote_handle(char *str, size_t *i)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (str[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_dquotes(char *str, size_t *i)
{
	char	*res;

	res = ft_strdup("\"");
	(*i)++;
	while (str[*i] != '"')
	{
		if (str[*i] == '$')
			res = ft_strjoin_f(res, ft_dollar_handle(str, i));
		else
			res = ft_strjoin_f(res, ft_subdquote_handle(str, i));
	}
	(*i)++;
	return (ft_strjoin_f(res, ft_strdup("\"")));
}
