#include "minishell.h"

bool    ft_get_iolist(t_io_node **io_list)
{
    t_token_type    redir_type;
    t_io_node   *tmp_io_node;

    if (g.minishell.parser_error.type)
        return (false);
    while (g_minishell.current_token && ft_redir(g_minishell.current_token->type))
    {
        redir_type = g_minishell.current_token->type;
        ft_get_next_token();
        if (!g_minishell.current_token)
            return (ft_set_parse_error(E_SYNTAX), false);
        if (g_minishell.current_token != T_IDENTIFIER)
            return (ft_set_parse_error(E_SYNTAX), false);
        tmp_io_node = ft_new_ionode(redir_type, g_minishell.current_token->value);
        if (!tmp_io_node)
            return (ft_set_parse_error(E_MEM), false);
        ft_append_ionode(io_list, tmp_io_node);
        ft_get_next_token();
    }
    return(true);
}

bool    ft_join_args(char **args)
{
    char    *line;

    if (g.minishell.parser_error.type)
        return (false);
    if (!*args)
        *args = ft_strdup("");
    if (!*args)
        return (false);
    while (g_minishell.current_token && (g_minishell.current_token->type == T_IDENTIFIER))
    {
        line = *args;
        *args = ft_strjoin_with(*args, g_minishell.current_node -> value, ' ');
        if (!*args)
            return (free(line), false);
        free(line);
        ft_get_next_token();
    }
}

t_node  ft_get_simple_cmd(void)
{
    t_node  *node;
    if (g.minishell.parser_error.type)
        return (false);
    node = ft_new_node(N_CMD);
    if (!node)
        return(ft_set_parse_error(E_MEM), NULL);
    while (g_minishell.current_token && (g_minishell.current_token->type == T_IDENTIFIER) 
                || ft_redir(g_minishell.current_token->type))
    {
        if (g_minishell.current_token->type == T_IDENTIFIER)
        {
            if (!ft_join_args(&(node -> args)))
                return (ft_clear_cmd_node(node), ft_set_parse_error(E_MEM), NULL);
        }
        else if (ft_redir(g_minishell.current_token->type))
        {
            if (!ft_get_iolist(&(node->io_list)))
                return (free(node->args), free(node), NULL);
        }
    }
    return (node);
}