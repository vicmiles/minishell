/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkhut <vkhut@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:37:00 by vkhut             #+#    #+#             */
/*   Updated: 2025/05/07 13:37:17 by vkhut            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_minishell;

static void	ft_init_minishell(char **env)
{
	ft_memset(&g_minishell, 0, sizeof(t_minishell));
	g_minishell.environ = env;
	ft_init_envlist();
	g_minishell.stdin = dup(0);
	g_minishell.stdout = dup(1);
	tcgetattr(STDIN_FILENO, &g_minishell.original_term);
}

static void	ft_start_execution(void)
{
	signal(SIGQUIT, ft_sigquit_handle);
	ft_init_tree(g_minishell.ast);
	if (g_minishell.heredoc_sigint)
	{
		ft_clear_ast(&g_minishell.ast);
		g_minishell.heredoc_sigint = false;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &g_minishell.original_term);
	g_minishell.exit_s = ft_exec_node(g_minishell.ast, false);
	ft_clear_ast(&g_minishell.ast);
}

int	main(int argc, char **argv, char **env)
{
	((void)argc, (void)argv);
	ft_init_minishell(env);
	while (1)
	{
		ft_signals();
		g_minishell.line = readline("minishell$ ");
		if (!g_minishell.line)
			(ft_clean_ms(),
				ft_putstr_fd("exit\n", 1), exit(g_minishell.exit_s));
		if (g_minishell.line[0])
			add_history(g_minishell.line);
		g_minishell.tokens = ft_lexer();
		if (!g_minishell.tokens)
			continue ;
		g_minishell.ast = ft_parse();
		if (g_minishell.parser_error.type)
		{
			ft_manage_parser_error();
			continue ;
		}
		ft_start_execution();
	}
	ft_garbage_collector(NULL, true);
	return (ft_clean_ms(), g_minishell.exit_s);
}
