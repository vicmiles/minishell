/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_empty_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:21:30 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 13:44:17 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_clean_empty_str(char *str)
{
	size_t	i;
	size_t	j;
	char	*temp;
	char	*res;
	size_t	memsize;

	if ((str[0] == '\'' && str[1] == '\'' && !str[2]) \
		|| (str[0] == '"' && str[1] == '"' && !str[2]))
		return (str);
	temp = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '"' && str[i + 1] == '"'))
			i += 2;
		else
			temp[j++] = str[i++];
	}
	free(str);
	memsize = ft_strlen(temp) + 1;
	res = ft_calloc(memsize, sizeof(char));
	return (ft_strlcpy(res, temp, memsize), free(temp), res);
}
