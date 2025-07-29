/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmileshk <vmileshk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 11:33:56 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 11:33:57 by vmileshk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_handle_clr(t_list **head, void (*del)(void *))
{
	ft_lstclear(head, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*nlst;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	content = f(lst -> content);
	head = ft_lstnew(content);
	if (!head)
		return (del(content), ft_handle_clr(&head, del), NULL);
	nlst = head;
	lst = lst -> next;
	while (lst)
	{
		content = f(lst -> content);
		nlst -> next = ft_lstnew(content);
		nlst = nlst -> next;
		if (!nlst)
			return (del(content), ft_handle_clr(&head, del), NULL);
		lst = lst -> next;
	}
	nlst -> next = NULL;
	return (head);
}
