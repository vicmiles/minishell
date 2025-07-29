/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 12:43:13 by vkhut             #+#    #+#             */
/*   Updated: 2025/05/07 12:43:22 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_out(t_io_node *io_list, int *status)
{
	int		fd;

	if (!io_list->expand_value || io_list->expand_value[1])
	{
		*status = ft_err_msg(
				(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
		return (*status);
	}
	fd = open(io_list->expand_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*status = ft_err_msg(ft_check_write(io_list->expand_value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	ft_in(t_io_node *io_list, int *status)
{
	int		fd;

	if (!io_list->expand_value || io_list->expand_value[1])
	{
		*status = ft_err_msg(
				(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
		return (*status);
	}
	fd = open(io_list->expand_value[0], O_RDONLY);
	if (fd == -1)
	{
		*status = ft_err_msg(ft_check_read(io_list->expand_value[0]));
		return (*status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}

int	ft_append(t_io_node *io_list, int *status)
{
	int	fd;

	if (!io_list->expand_value || io_list->expand_value[1])
	{
		*status = ft_err_msg(
				(t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_list->value});
		return (*status);
	}
	fd = open(io_list->expand_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = ft_err_msg(ft_check_write(io_list->expand_value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (0);
}
