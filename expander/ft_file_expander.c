/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_expander.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:39:49 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 13:37:05 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	ft_file_visiability(char *pattern, char *str)
{
	if ((pattern[0] == '.' && str[0] == '.') \
	|| (pattern[0] != '.' && str[0] != '.'))
		return (true);
	return (false);
}

static bool	ft_handle_direct(struct dirent **entry, DIR *dir)
{
	*entry = readdir(dir);
	return (true);
}

static char	**ft_globber_handler(char *str)
{
	char			**result;
	DIR				*dir;
	struct dirent	*entry;
	size_t			count_match;

	count_match = ft_count_match(str);
	if (!ft_contain_star(str) || !count_match)
	{
		result = (char **)ft_calloc(2, sizeof(char *));
		result[0] = ft_strdup(str);
		return (result);
	}
	else
	{
		dir = opendir(".");
		result = (char **)ft_calloc(count_match + 1, sizeof(char *));
		count_match = 0;
		while (ft_handle_direct(&entry, dir) && entry)
			if (ft_star_match(str, entry->d_name) \
					&& ft_file_visiability(str, entry->d_name))
				result[count_match++] = ft_strdup(entry->d_name);
		closedir(dir);
	}
	return (result);
}

char	**ft_file_expander(char **expand)
{
	size_t	i;
	size_t	expand_len;
	char	***globb;

	expand_len = ft_arraystr_len(expand);
	globb = (char ***)ft_calloc(expand_len + 1, sizeof(char **));
	i = 0;
	while (expand[i])
	{
		globb[i] = ft_globber_handler(expand[i]);
		i++;
	}
	return (ft_free_char2(expand), ft_arraystr_join(globb));
}
