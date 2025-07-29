/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:51:06 by vmileshk          #+#    #+#             */
/*   Updated: 2025/05/07 13:38:22 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint_handler(int num)
{
	(void)num;
	if (g_minishell.signint_child)
	{
		ft_putstr_fd("\n", 1);
		g_minishell.signint_child = false;
		g_minishell.heredoc_sigint = true;
	}
	else
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_sigquit_handle(int num)
{
	(void)num;
	ft_putstr_fd("Quit: 3\n", 1);
}

void	ft_signals(void)
{
	struct termios	term;

	term = g_minishell.original_term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	g_minishell.heredoc_sigint = false;
	g_minishell.signint_child = false;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
