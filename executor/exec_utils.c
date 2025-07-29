/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:45:14 by vkhut             #+#    #+#             */
/*   Updated: 2025/05/07 13:10:43 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_error(int error_code, const char *cmd)
{
	if (error_code == ENO_NOT_FOUND)
		fprintf(stderr, "%s: command not found \n", cmd);
	else if (error_code == ENO_CANT_EXEC)
		fprintf(stderr, "%s: permission denied\n", cmd);
	else
		fprintf(stderr, "%s: unknown error\n", cmd);
}

void	*ft_garbage_collector(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}

bool	ft_is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}
