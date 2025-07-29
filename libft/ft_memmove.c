/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:34:27 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 11:34:27 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst - src > 0)
	{
		while (len--)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
		return ((void *)dst);
	}
	return (ft_memcpy(dst, src, len));
}
