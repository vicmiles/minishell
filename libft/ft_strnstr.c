/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:36:24 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 11:36:24 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cmp(const char *s1, const char *s2, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (!s2[i])
		return (1);
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if ((!haystack || !needle) && !len)
		return (NULL);
	if (!ft_strlen(needle))
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
			if (ft_cmp(haystack + i, needle, len - i))
				return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
