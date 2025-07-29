/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:33:33 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 11:33:35 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*curr;

	if (!lst || !*lst || !del)
		return ;
	curr = *lst;
	next = curr -> next;
	while (curr && next)
	{
		del(curr -> content);
		free(curr);
		curr = next;
		next = curr -> next;
	}
	del(curr -> content);
	free(curr);
	*lst = NULL;
}
