/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:18:02 by vkhut             #+#    #+#             */
/*   Updated: 2025/05/07 13:18:03 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_heredoc_sigint_handle(int signal)
{
	(void)signal;
	ft_clean_ms();
	exit(SIGINT);
}

void	ft_heredoc(t_io_node *io, int p[2])
{
	char	*line;
	char	*quote;

	signal(SIGINT, ft_heredoc_sigint_handle);
	quote = io->value;
	while (*quote && *quote != '"' && *quote != '\'')
		quote++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_is_delimiter(io->value, line))
			break ;
		if (!*quote)
			ft_expand_heredoc(line, p[1]);
		else
		{
			ft_putstr_fd(line, p[1]);
			ft_putstr_fd("\n", p[1]);
		}
	}
	ft_clean_ms();
	exit(0);
}

static bool	ft_leave_child(int p[2], int *pid)
{
	waitpid(*pid, pid, 0);
	signal(SIGQUIT, ft_sigquit_handle);
	g_minishell.signint_child = false;
	close(p[1]);
	if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
		return (true);
	return (false);
}

static void	ft_init_child(t_node *node)
{
	t_io_node	*io;
	int			p[2];
	int			pid;

	if (node->args)
		node->expand_args = ft_expand(node->args);
	io = node->io_list;
	while (io)
	{
		if (io->type == IO_HEREDOC)
		{
			pipe(p);
			g_minishell.signint_child = true;
			pid = (signal(SIGQUIT, SIG_IGN), fork());
			if (!pid)
				ft_heredoc(io, p);
			if (ft_leave_child(p, &pid))
				return ;
			io->here_doc = p[0];
		}
		else
			io->expand_value = ft_expand(io->value);
		io = io->next;
	}
}

void	ft_init_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->type == N_PIPE || node->type == N_AND || node->type == N_OR)
	{
		ft_init_tree(node->left);
		if (!g_minishell.heredoc_sigint)
			ft_init_tree(node->right);
	}
	else
		ft_init_child(node);
}
