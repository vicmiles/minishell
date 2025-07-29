/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:26:49 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 13:38:19 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_skip_word(char const *str, size_t *i)
{
	char	quote;

	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i] != '\'' && str[*i] != '"')
			(*i)++;
		else
		{
			quote = str[(*i)++];
			while (str[*i] != quote)
				(*i)++;
			(*i)++;
		}
	}
}

static char	**ft_memory_allocate(char const *str, char **strs)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			start = i;
			ft_skip_word(str, &i);
			strs[j] = ft_calloc(i - start + 1, sizeof(char));
			if (!strs[j])
				return (NULL);
			j++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (strs);
}

static void	ft_word_fill(const char *str, char **strs, size_t *i, size_t j)
{
	char	quote;
	size_t	k;

	k = 0;
	while (str[(*i)] && str[(*i)] != ' ')
	{
		if (str[(*i)] != '\'' && str[(*i)] != '"')
			strs[j][k++] = str[(*i)++];
		else
		{
			quote = str[(*i)++];
			strs[j][k++] = quote;
			while (str[(*i)] != quote)
				strs[j][k++] = str[(*i)++];
			strs[j][k++] = str[(*i)++];
		}
	}
}

static char	**ft_fill(const char *str, char **strs)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i] && strs[j])
	{
		if (str[i] != ' ')
		{
			ft_word_fill(str, strs, &i, j);
			j++;
		}
		while (str[i] && str[i] == ' ')
			i++;
	}
	return (strs);
}

char	**ft_expand_split(const char *str)
{
	size_t	count;
	char	**strs;
	char	**temp;
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != ' ' && ++count)
			ft_skip_word(str, &i);
		while (str[i] && str[i] == ' ')
			i++;
	}
	strs = ft_calloc(count + 1, sizeof(char *));
	temp = strs;
	strs = ft_memory_allocate(str, strs);
	if (!strs || !count)
	{
		return (ft_free_char2(temp), NULL);
	}
	return (ft_fill(str, strs));
}
